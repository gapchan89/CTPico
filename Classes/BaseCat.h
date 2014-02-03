/*
 *  BaseCat.h
 *  Untitled
 *
 *  Created by Guo Wei Tan on 1/20/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */
#ifndef _BASE_CAT_H_
#define _BASE_CAT_H_

#include "cocos2d.h"
#include "EnumCatState.h"
#include "Character/Character.h"

using namespace cocos2d;

class BaseCat: public CCSprite
{
protected:
	int				_speedX, _speedY,
					_health,
					_floorY; //used for jump animation
	bool			_hasSkill, _skillReady;
	float			_speedMultiplier,
					_skillCoolDown, _skillCoolDownTimer;
	EnumCatState	_catState;

	CCAnimate* 		_pRunningAnimate;
	//CCAnimate* 	_pAttackAnimate;
	//CCAnimate* 	_pSkillAnimate;

	void loadSprite();
	void useSkill(float timeDiff);
	void attack(float timeDiff, Character* charRef);
	void move(float timeDiff, GameMap* mapRef);
	void reduceCoolDown(float timeDiff);

public:
	static const int BASE_SPEED = 10; //x and y speed
	static const int BASE_ATK_SPEED = BASE_SPEED * 2;
	static const int BASE_JUMP_HEIGHT = 30;
	static const int BASE_COOLDOWN = 10000; //ms
	static const int BASE_HEALTH = 2;
	static const int BASE_DAMAGE = 1;

	//===== CONSTRUCTOR =====
	BaseCat(bool hasSkill);

	//===== FUNCTIONS =====
	void update(float timeDiff, GameMap* mapRef, Character* charRef);
	void reduceHealth(int healthReduction);

	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
	CC_SYNTHESIZE(CCTouch *, _touch, Touch);

	//===== STATIC FUNCTIONS =====
	static BaseCat*	gameSpriteWithFile(const char* filename);
	static BaseCat* gameSpriteWithFrame(CCSpriteFrame *frame);
	static CCSpriteFrame* createSpriteFrame();

	//===== GETTERS =====
	EnumCatState getState();
	bool hasSkill();
	bool isClicked();
	bool isDead();
	CCRect getRect();

	//===== SETTERS =====
	void setSpeedMultiplier(float multiplier);
	void setIsClicked(bool clicked);
	void setIsDead(bool dead);
};


#endif
