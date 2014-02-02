#include "CharacterAI.h"
//#include "SimpleAudioEngine.h"
#include "Map/GameMap.h"
#include "Character.h"

using namespace cocos2d;
//using namespace CocosDenshion;

CharacterAI::CharacterAI(Character* character, GameMap* map)
{
	_charReference = character;
	_mapReference = map;
}

CharacterAI::~CharacterAI(void)
{

}

void CharacterAI::update(float timeDiff)
{
	// Make decision based on character class
	// Set character state based on decision
	// Set character value based on decision
}
