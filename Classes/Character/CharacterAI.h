#ifndef __CHARACTERAI_H__
#define __CHARACTERAI_H__

#include "cocos2d.h"
#include "Character.h"
#include "Map/GameMap.h"

using namespace cocos2d;

class GameMap;		// Forward declaration
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
	CharacterAI(); 	//Default constructor
	CharacterAI(Character* character, GameMap* map);

	//===== DESTRUCTOR =====
	~CharacterAI(void);

	//===== FUNCTIONS =====
	void 				update(float timeDiff);
};

#endif // __CHARACTERAI_H__
