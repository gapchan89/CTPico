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
	_pDirectorSpawnScript = 0;

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
	runDirectorSpawnScript(timeDiff);

	//update all cats
	CCObject* cat = 0;
	CCARRAY_FOREACH(_cats, cat)
	{
		BaseCat* pCat = dynamic_cast<BaseCat*>(cat);
		pCat->update(timeDiff, _pMapRef, _pCharRef);
	}

	//remove any cats that is marked for deletion
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

void CatsManager::setLevelSpawnScript(CatSpawnScript* pCatSpawnScript)
{
	_pSpawnScript = pCatSpawnScript;
}

void CatsManager::insertDirectorSpawnSet(CatSpawnSet* pCatSpawnSet)
{

}



