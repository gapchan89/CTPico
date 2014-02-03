#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "EnumCharacterState.h"

using namespace cocos2d;

class GameMap;
//class LevelMode; //TODO: Fix it Felix

class Character : public CCSprite
{
private:

	//AI					_charBaseAI;			// AI class to decide on actions

	CCSprite*			_pCharSprite;			// Sprite to store character's sprite sheet
	CCAnimation*		_pCharAnimation;		// Animation for character
	
	int					_health;
	int					_immunityDuration;

	void				setupSprite();

public:

	//===== CONSTRUCTOR =====
	Character(); //Default constructor, temp
	Character(GameMap* map);

	//===== DESTRUCTOR =====
	~Character(void);
	//Character* 				gameSpriteWithFrame(CCSpriteFrame *frame);
	
	//===== FUNCTIONS =====
	static Character*		gameSpriteWithFile(const char* filename);
	static Character* 		gameSpriteWithFrame(CCSpriteFrame *frame);
	CCRect 					getRect();
	virtual void 			setPosition(const CCPoint& pos);

	//void 					setupAI(LevelMode levelMode);	// Choose which AI to set up based on level mode
	bool					reduceHealth(int health);		// Reduce character's health, if < 0, character dies
	void					update(float timeDiff);			// Update the character's action

	//===== GETTERS/SETTERS =====
	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
	CC_SYNTHESIZE(CCTouch *, _touch, Touch);

	CC_SYNTHESIZE(int, _speedX, SpeedX);
	CC_SYNTHESIZE(int, _speedY, SpeedY);
	CC_SYNTHESIZE(int, _obstacleHitChance, ObstacleHitChance);

	CC_SYNTHESIZE(EnumCharacterState, _charState, CharState);

	int						getHealth()				{	return _health;		}
	int						getImmunityDuration()	{	return _immunityDuration;		}

};

#endif // __CHARACTER_H__
