#ifndef __CATSMANAGER_H__
#define __CATSMANAGER_H__

#include "cocos2d.h"
#include "Character/Character.h"
#include "Map/GameMap.h"
#include "EnumLevelType.h"

class CatsManager
{
private:
	GameMap* _pMapRef;
	Character* _pCharRef;

public:
	//========== CONSTRUCTOR ==========
	CatsManager(void);
	//========== DESTRUCTOR ==========
	~CatsManager(void);

	//========== FUNCTIONS ==========s
	void update(float timeDiff);
	void setupAI(EnumLevelType levelType);
};

#endif // __CATSMANAGER__
