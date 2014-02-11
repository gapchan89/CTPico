#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "EnumCharacterState.h"
#include "CharacterAI.h"
#include "Map/GameMap.h"

using namespace cocos2d;

class GameMap;		// Forward declaration
//class LevelMode; 	//TODO: Fix it Felix

class Character : public CCSprite
{
private:

	static const int 	BASE_SPEED = 15; 				// x and y speed
	static const int 	BASE_HEALTH = 3;
	static const int 	BASE_OBSTACLE_HIT_CHANCE = 10;	// %
	static const int	BASE_IMMUNITY = 2000;			// ms
	static const int 	DEFAULT_MOVED = 0;
	static const int 	STOP_SPEED = 4; 				// rate at which character stops

	static const float 	BASE_SPEED_MULITIPLIER = 1.0;

	// SYNTHESIZE: _nextPosition, _vector, _touch, _speedX, _speedY, _obstacleHitChance, _charState, _speedMultiplier

	CharacterAI*		_pCharBaseAI;			// AI class to decide on actions

	CCSprite*			_pCharSprite;			// Sprite to store character's sprite sheet
	CCAnimation*		_pCharAnimation;		// Animation for character
	CCAnimate* 			_pRunningAnimate;

	int					_health;
	float				_immunityDuration;		// Count down to 0 before being vulnerable

	int					_maxMoveDistance;
	int					_amountMoved;

	void				initVariables();
	void				loadSprite();
	void				runUp(float timeDiff);
	void				runDown(float timeDiff);
	void				stop(float timeDiff);
	bool				canMove(float moveAmount);
	bool				isImmune();

public:

	//===== CONSTRUCTOR =====
	Character(); 				//Default constructor, temp
	Character(GameMap* map);

	//===== DESTRUCTOR =====
	~Character(void);
	
	//===== STATIC FUNCTIONS =====
	static Character*		gameSpriteWithFile(const char* filename, GameMap* map);
	static Character* 		gameSpriteWithFrame(CCSpriteFrame *frame, GameMap* map);
	static CCSpriteFrame* 	createSpriteFrame();

	//===== FUNCTIONS =====
	CCRect 					getRect();
	virtual void 			setPosition(const CCPoint& pos);
	//void 					setupAI(LevelMode levelMode);	// Choose which AI to set up based on level mode
	void					reduceHealth(int health);		// Reduce character's health, if < 0, character dies
	void					update(float timeDiff);			// Update the character's action

	//===== GETTERS/SETTERS =====
	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
	CC_SYNTHESIZE(CCTouch *, _touch, Touch);

	CC_SYNTHESIZE(int, _speedX, SpeedX);
	CC_SYNTHESIZE(int, _speedY, SpeedY);
	CC_SYNTHESIZE(int, _obstacleHitChance, ObstacleHitChance);
	CC_SYNTHESIZE(EnumCharacterState, _charState, CharState);
	CC_SYNTHESIZE(float, _speedMultiplier, SpeedMultiplier);

	int						getHealth()				{	return _health;		}
	int						getImmunityDuration()	{	return _immunityDuration;		}

};

#endif // __CHARACTER_H__
