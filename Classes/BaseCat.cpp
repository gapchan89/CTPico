/*
 *  BaseCat.cpp
 *  Untitled
 *
 *  Created by Guo Wei Tan on 1/20/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include "BaseCat.h"

//===== CONSTRUCTOR =====
BaseCat::BaseCat(bool hasSkill)
{
	_speedX = _speedY = BaseCat::BASE_SPEED;
	_skillCoolDown = _skillCoolDownTimer = BaseCat::BASE_COOLDOWN;
	_health = BaseCat::BASE_HEALTH;
	_hasSkill = hasSkill;
	_skillReady = true;
	_speedMultiplier = 1.0;
	_catState = CAT_CHASE;

	//load sprites and animation
	loadSprite();
}

//===== FUNCTIONS =====

/*!
    @function loadSprite
    @result		loads the sprite and all the relevant animation of the cat
 */
void BaseCat::loadSprite()
{
	//========== ANIMATE IMAGE ==========
	CCAnimation *runningAnimation = CCAnimation::create();
	//load the frames of animation
	for (int i = 0; i < 4; i++)
	{
		CCSpriteFrame *frame = CCSpriteFrame::create("Game/Cats/punk cat.png", CCRect(i*100, 0, 100, 100));
		runningAnimation->addSpriteFrame(frame);
	}
	//setup animation properties
	runningAnimation->setDelayPerUnit(0.2); // This animation contains 14 frames, will continuous 2.8 seconds.
	runningAnimation->setLoops(10000);
	runningAnimation->setRestoreOriginalFrame(true); // Return to the 1st frame after the 14th frame is played.

	_pRunningAnimate = CCAnimate::create(runningAnimation);

	//start animating the running
	this->runAction(_pRunningAnimate);
}

void BaseCat::useSkill(float timeDiff)
{

}

/*!
    @function attack
    @param		timeDiff:float
				time difference since the last call
	@param		charRef:Character*
				reference to the character
    @result		moves the cat based on BASE_ATK_SPEED and multiplier.
    			will check for collision between the character and the cat.
    			if collided, reduces the character's health by BASE_DAMAGE and sets cat state to DEAD.
 */
void BaseCat::attack(float timeDiff, Character* charRef)
{
	//move quickly towards the character's position (homing)
	this->setPositionX(this->getPositionX() + (BASE_ATK_SPEED * timeDiff) * _speedMultiplier);
	this->setPositionY(this->getPositionY() + (BASE_ATK_SPEED * timeDiff) * _speedMultiplier);

	//if collided
	if (this->getRect().intersectsRect(charRef->getRect()))
	{
		//reduce character health
		charRef->reduceHealth(BASE_DAMAGE);
		//delete this cat (mark for deletion)
		_catState = CAT_DEAD;
	}
}

/*!
    @function move
    @param		timeDiff:float
				time difference since the last call
	@param		mapRef:GameMap*
				reference to the game map
    @result		moves the cat based on its current speed and multiplier.
    			cat will jump if it hits an obstacle
 */
void BaseCat::move(float timeDiff, GameMap* mapRef)
{
	//update position to move towards left of screen based on speed (LEFT SIDE, MINUS)
	this->setPositionX(this->getPositionX() - (_speedX * timeDiff) * _speedMultiplier);

	//current state is jumping (mid air)
	if (_catState = CAT_CHASE_JUMP)
	{
		//update movement
		this->setPositionY(this->getPositionY() + (_speedY * timeDiff) * _speedMultiplier);

		//moving upwards and reached the peak
		if (_speedY > 0 && this->getPositionY() >= _floorY + BaseCat::BASE_JUMP_HEIGHT)
			_speedY = -_speedY;
		//moving downwards and reached the floor
		else if (_speedY < 0 && this->getPositionY() <= _floorY)
		{
			this->setPositionY(_floorY);
			_speedY = -_speedY;
			//set state back to normal running
			_catState = CAT_CHASE;
		}
	}

	//if collided with obstacle
	if (mapRef->checkCollision(this->getPosition()))
		_catState = CAT_CHASE_JUMP;
}

/*!
    @function reduceCoolDown
    @param		timeDiff:float
				time difference since the last call
    @result		reduces the cool down timer of the skill.
    			sets _skillReady to be true when cool down reaches 0.
    			resets the timer when it reaches 0.
 */
void BaseCat::reduceCoolDown(float timeDiff)
{
	//if already cooled down
	if (_skillReady)
		return;

	_skillCoolDownTimer -= timeDiff;
	//skill ready for use
	if ( _skillCoolDownTimer <= 0)
	{
		_skillReady = true;
		//reset the timer
		_skillCoolDownTimer = _skillCoolDown;
	}
}

/*!
    @function update
    @param		timeDiff:float
				time difference between the last update call
    @result		base on the state the cat is in, call corresponding functions
 */
void BaseCat::update(float timeDiff, GameMap* mapRef, Character* charRef)
{
	//get new state from AI if cat is not in mid air / jumping
	/*if (!_catState.CHASE_JUMP)
		_catState = AI.GETSTATE();*/

	//update the skill cool down if possible
	if (_hasSkill)
		reduceCoolDown(timeDiff);

	//act according to state
	switch(_catState)
	{
		//cat dead
		case CAT_DEAD:
			return;

		//move
		case CAT_CHASE:
		case CAT_CHASE_JUMP:
			move(timeDiff, mapRef);
			break;

		//stop
		case CAT_STOP:
			//stop the cat?
			//TODO:
			break;

		//attack
		case CAT_ATTACK:
			attack(timeDiff, charRef);
			break;

		//skill
		case CAT_SKILL:
			useSkill(timeDiff);
			break;
	}
}

/*!
    @function reduceHealth
    @param		healthReduction:int
				the amount of health to reduce from the cat
    @result		reduces the specified amount of health from the cat.
    			if the health reaches 0, sets the state of the cat to be EnumCatState.DEAD
 */
void BaseCat::reduceHealth(int healthReduction)
{
	_health -= healthReduction;

	if (_health <= 0)
		_catState = CAT_DEAD;
}


//===== STATIC FUNCTIONS =====

BaseCat* BaseCat::gameSpriteWithFrame(CCSpriteFrame *frame)
{
	BaseCat *cat = new BaseCat(false);

	if( cat && cat->initWithSpriteFrame(frame) )
	{
		cat->autorelease();
		return cat;
	}

	CC_SAFE_DELETE(cat);
	return NULL;
}

BaseCat* BaseCat::gameSpriteWithFile(const char* filename)
{
	BaseCat *cat = new BaseCat(false);

	if( cat && cat->initWithFile(filename))
	{
		cat->autorelease();
		return cat;
	}

	CC_SAFE_DELETE(cat);
	return NULL;
}

/*!
    @function createSpriteFrame
    @result		creates a CCSpriteFrame based on this cat
 */
CCSpriteFrame* BaseCat::createSpriteFrame()
{
	return CCSpriteFrame::create("Game/Cats/punk cat.png", CCRect(0, 0,100,100) );
}

//===== GETTERS =====

EnumCatState BaseCat::getState()
{
	return _catState;
}

bool BaseCat::hasSkill()
{
	return _hasSkill;
}

bool BaseCat::isClicked()
{
	//TODO: FIX
	return true;
}

bool BaseCat::isDead()
{
	return _catState == CAT_DEAD;
}

CCRect BaseCat::getRect()
{
	return CCRectMake(this->getPosition().x - (this->getContentSize().width/2),
						this->getPosition().y - (this->getContentSize().height/2),
						this->getContentSize().width,
						this->getContentSize().height);
}

//===== SETTERS =====
void BaseCat::setSpeedMultiplier(float multiplier)
{
	_speedMultiplier = multiplier;
}

void BaseCat::setIsClicked(bool clicked)
{
	//TODO:FIX
}

void BaseCat::setIsDead(bool dead)
{
	if (dead)
		_catState = CAT_DEAD;
	else
		_catState = CAT_CHASE;
}
