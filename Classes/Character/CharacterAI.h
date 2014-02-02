#ifndef __CHARACTERAI_H__
#define __CHARACTERAI_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameMap;
class Character;

class CharacterAI
{
private:

	Character*			_charReference;
	GameMap*			_mapReference;

public:
	CharacterAI(Character* character, GameMap* map);
	~CharacterAI(void);

	void 				update(float timeDiff);
};

#endif // __CHARACTERAI_H__
