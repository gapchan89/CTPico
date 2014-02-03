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
	float				_amountMoved;		// Updates each time the character 'moves'
	bool				_isStop;			// Check is Character is told to stop

	bool				isNewGrid();

public:
	//===== CONSTRUCTOR =====
	CharacterAI(Character* character, GameMap* map);

	//===== DESTRUCTOR =====
	~CharacterAI(void);

	//===== FUNCTIONS =====
	void 				update(float timeDiff);
};

#endif // __CHARACTERAI_H__
