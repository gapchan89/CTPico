#include "CatsManager.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;


//========== CONSTRUCTOR ==========

CatsManager::CatsManager(int levelType, GameMap* pMapRef, Character* pCharRef, GameManager* pGmRef)
{
	_levelType = levelType;
	_pMapRef = pMapRef;
	_pCharRef = pCharRef;
	_pGmRef = pGmRef;

	_pSpawnScript = 0;
	_pDirectorSpawnSets = new CCArray();

	_cats = new CCArray();
}

//========== DESTRUCTOR ==========

CatsManager::~CatsManager()
{
	_pMapRef = 0;
	_pCharRef = 0;

	CCObject* cat = 0;
	CCARRAY_FOREACH(_cats, cat)
	{
		BaseCat* pCat = dynamic_cast<BaseCat*>(cat);
		delete pCat;
	}

	_cats->release();
	delete _cats;
}

//========== FUNCTIONS ==========
void CatsManager::update(float timeDiff)
{
	//check spawn script
	runSpawnScript(timeDiff);
	//check additional spawn script
	runDirectorSpawnSets(timeDiff);

	//update all cats in the game
	updateAllCats(timeDiff);
	//remove cats that are dead / marked for deletion
	removeDeadCats();


}

void CatsManager::removeDeadCats()
{
	//remove any cats that is marked for deletion
	CCObject* cat = 0;
	CCARRAY_FOREACH(_cats, cat)
	{
		BaseCat* pCat = dynamic_cast<BaseCat*>(cat);
		if (pCat->getState() == CAT_DEAD)
		{
			_pGmRef->removeChild(pCat);
			_cats->removeObject(pCat, true);
			delete pCat;
		}
	}
}

void CatsManager::updateAllCats(float timeDiff)
{
	//update all cats
	CCObject* cat = 0;
	CCARRAY_FOREACH(_cats, cat)
	{
		BaseCat* pCat = dynamic_cast<BaseCat*>(cat);
		pCat->update(timeDiff, _pMapRef, _pCharRef);
	}
}

void CatsManager::runSpawnScript(float timeDiff)
{
	if (_pSpawnScript == 0)
		return;

	//retrieve array of cat types to be added if any
	CCArray* pCatTypesToSpawn = _pSpawnScript->updateAndCheckForSpawns(timeDiff);;

	//add cats into the game
	CCObject* catType = 0;
	CCARRAY_FOREACH(pCatTypesToSpawn, catType)
	{
		CCInteger* catTypeInt = dynamic_cast<CCInteger*>(catType);
		createCat(catTypeInt->getValue());

		//clean up
		catTypeInt->release();
		delete catTypeInt;
	}
	//clean up
	pCatTypesToSpawn->release();
	delete pCatTypesToSpawn;

}

void CatsManager::runDirectorSpawnSets(float timeDiff)
{

}

void CatsManager::createCat(int catType)
{
	//TODO:
	//create the cat
}

void CatsManager::setLevelSpawnScript(CatSpawnScript* pCatSpawnScript)
{
	_pSpawnScript = pCatSpawnScript;
}

void CatsManager::insertDirectorSpawnSet(CatSpawnSet* pCatSpawnSet)
{
	_pDirectorSpawnSets->addObject(pCatSpawnSet);
}



