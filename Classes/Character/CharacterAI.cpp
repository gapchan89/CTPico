#include "CharacterAI.h"
//#include "SimpleAudioEngine.h"
#include "Map/GameMap.h"
#include "Character.h"
#include "EnumCharacterState.h"

using namespace cocos2d;
//using namespace CocosDenshion;

//===== CONSTRUCTOR =====
CharacterAI::CharacterAI(Character* character, GameMap* map)
{
	_charReference = character;
	_mapReference = map;
	_amountMoved = 0;
	_isStop = false;
}

//===== DESTRUCTOR =====
CharacterAI::~CharacterAI(void)
{

}

//===== PUBLIC FUNCTIONS =====
void CharacterAI::update(float timeDiff)
{
	// Make decision based on character class
	// Set character state based on decision
	// Set character value based on decision

	// Random value to determine obstacle hit chance
	int obstacleHitChance = arc4random() % 100;

	// Update the amount the character has moved
	_amountMoved += _charReference->getSpeedX();

	// Check for collision if character is not colliding
	if( _charReference->getCharState() != STOP )
	{
		// If the character has hit an obstacle
		if( obstacleHitChance < _charReference->getObstacleHitChance())
		{
			//_mapReference->getNextGrid(true, _charReference->getPositionY());
			_charReference->setCharState(STOP);
			_isStop = true;
		}
	}
	else
	{
		// Not colliding, update Char states
		_isStop = false;
	}

	// Update the Character y-coord if he runs into a new grid
	if( isNewGrid() && !_isStop )
	{
		// Update Character's state
		//EnumCharacterState _newCharState = _mapReference->getNextGrid(false, _charReference->getPositionY());
		//_charReference->setCharState(_newCharState);
	}

}

//===== PRIVATE FUNCTIONS =====
bool CharacterAI::isNewGrid()
{
	// Check if the character has moved out of the current grid
	if(_amountMoved >= _mapReference->getPixelsPerGrid())
	{
		_amountMoved = 0;
		return true;
	}

	return false;
}

