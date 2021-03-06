#ifndef __CATSMANAGER_H__
#define __CATSMANAGER_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "Map/GameMap.h"
#include "EnumLevelType.h"
#include "Levels/CatSpawnScript.h"
#include "Levels/CatSpawnSet.h"
#include "Cats/BaseCat.h"
#include "Cats/EnumCatType.h"
#include "EnumCatState.h"
#include "GameManager.h"

class CatsManager
{
private:
	GameMap* 	_pMapRef;
	Character* 	_pCharRef;
	GameManager* _pGmRef;
	int 		_levelType;
	CCArray* 	_cats;
	CatSpawnScript* _pSpawnScript;
	CCArray* 		_pDirectorSpawnSets; //for ai director insertion


	void removeDeadCats();
	void updateAllCats(float timeDiff);
	void runSpawnScript(float timeDiff);
	void runDirectorSpawnSets(float timeDiff);
	BaseCat* createCat(int catType);



public:
	//========== CONSTRUCTOR ==========
	CatsManager(int levelType, GameMap* pMapRef, Character* pCharRef, GameManager* pGmRef);
	//========== DESTRUCTOR ==========
	~CatsManager(void);

	//========== FUNCTIONS ==========
	void update(float timeDiff);
	void setLevelSpawnScript(CatSpawnScript* pCatSpawnScript);
	void insertDirectorSpawnSet(CatSpawnSet* pCatSpawnSet);

};

#endif // __CATSMANAGER__
