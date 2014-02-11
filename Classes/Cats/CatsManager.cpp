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
	//remove cats that are dead / marked for deletion
	removeDeadCats();

	//update all cats in the game
	updateAllCats(timeDiff);

	//check spawn script
	runSpawnScript(timeDiff);

	//check additional spawn script
	runDirectorSpawnSets(timeDiff);

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

	//loop through all new cats to spawn into the game
	CCObject* catType = 0;
	CCARRAY_FOREACH(pCatTypesToSpawn, catType)
	{
		CCInteger* catTypeInt = dynamic_cast<CCInteger*>(catType);
		//create cat
		BaseCat* newCat = createCat(catTypeInt->getValue());

		//add to the game
		_cats->addObject(newCat);

		//clean up the integer array
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

BaseCat* CatsManager::createCat(int catType)
{
	//TODO:
	//create the cat
	BaseCat* cat;
	switch (catType)
	{
		case BOUNCE_CAT:
		break;

		case COWBOY_CAT:
		break;

		case FAT_CAT:
		break;

		case NINJA_CAT:
		break;

		case OLYMPIC_CAT:
		break;

		case PEW_CAT:
		break;

		case PUNK_CAT:
		break;

		case WITCH_CAT:
		break;

		default: //BASE_CAT
			cat = new BaseCat();
			break;
	}
	return cat;
}

void CatsManager::setLevelSpawnScript(CatSpawnScript* pCatSpawnScript)
{
	_pSpawnScript = pCatSpawnScript;
}

void CatsManager::insertDirectorSpawnSet(CatSpawnSet* pCatSpawnSet)
{
	_pDirectorSpawnSets->addObject(pCatSpawnSet);
}



