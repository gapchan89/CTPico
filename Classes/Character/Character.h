#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameMap;
//class LevelMode; //TOFIX

class Character : public CCSprite
{
private:

	//AI					_charBaseAI;			// AI class to decide on actions

	CCSprite*			_pCharSprite;			// Sprite to store character's sprite sheet
	CCAnimation*		_pCharAnimation;		// Animation for character

	//CharacterStateEnum	_charState;				// Run/Stop state for Character
	
	int					_speedX;
	int					_speedY;
	int					_health;
	int					_immunityDuration;
	int					_obstacleHitChance;

	void				setupSprite();

public:
	Character(); //Default constructor, temp
	Character(GameMap* map);
	~Character(void);
	//Character* 				gameSpriteWithFrame(CCSpriteFrame *frame);

	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
	CC_SYNTHESIZE(CCTouch *, _touch, Touch);
 
	int						getSpeedX()				{	return _speedX;		}
	void					setSpeedX(int speedX)	{	_speedX = speedX;	}
	
	int						getSpeedY()				{	return _speedY;		}
	void					setSpeedY(int speedY)	{	_speedY = speedY;	}
	
	int						getHealth()				{	return _health;		}

	int						getImmunityDuration()	{	return _immunityDuration;		}
	
	int						getObstacleHitChance()						{	return _obstacleHitChance;				}
	void					setObstacleHitChance(int obstacleHitChance)	{	_obstacleHitChance = obstacleHitChance;	}
	
	static Character*		gameSpriteWithFile(const char* filename);
	static Character* 		gameSpriteWithFrame(CCSpriteFrame *frame);
	virtual void 			setPosition(const CCPoint& pos);

	//void 					setupAI(LevelMode levelMode);	// Choose which AI to set up based on level mode
	bool					reduceHealth(int health);		// Reduce character's health, if < 0, character dies
	void					update(float timeDiff);			// Update the character's action

};

#endif // __CHARACTER_H__
