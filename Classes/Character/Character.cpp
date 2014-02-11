#include "EnumLevelType.h"
#include "Character.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;
//using namespace CocosDenshion;

//===== CONSTRUCTOR =====
Character::Character()
{
	initVariables();
}

Character::Character(GameMap* map)
{
	// SYNTHESIZE: _nextPosition, _vector, _touch, _speedX, _speedY, _obstacleHitChance, _charState, _speedMultiplier

	_maxMoveDistance = map->getPixelsPerGrid();
	
	initVariables();

	//setupAI();
	_pCharBaseAI = new CharacterAI(this, map);		// AI class to decide on actions
}

void Character::initVariables()
{
	_amountMoved = DEFAULT_MOVED;

	_health = BASE_HEALTH;
	_immunityDuration = 0;

	setSpeedX(BASE_SPEED);
	setSpeedY(BASE_SPEED);
	setObstacleHitChance(BASE_OBSTACLE_HIT_CHANCE);
	setCharState(RUN);
	setSpeedMultiplier(BASE_SPEED_MULITIPLIER);
}

//===== DESTRUCTOR =====
Character::~Character(void)
{

}

//===== FUNCTIONS =====
Character* Character::gameSpriteWithFrame(CCSpriteFrame *frame, GameMap* map)
{
	Character *character = new Character(map);

	if( character && character->initWithSpriteFrame(frame) )
	{
		character->loadSprite();
		character->autorelease();
		return character;
	}

	CC_SAFE_DELETE(character);
	return NULL;
}

Character* Character::gameSpriteWithFile(const char* filename, GameMap* map)
{
	Character *character = new Character(map);

	if( character && character->initWithFile(filename))
	{
		character->autorelease();
		return character;
	}

	CC_SAFE_DELETE(character);
	return NULL;
}

/*!
    @function createSpriteFrame
    @result		creates a CCSpriteFrame based on this cat
 */
CCSpriteFrame* Character::createSpriteFrame()
{
	return CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(0, 100,100,100) );
}

void Character::loadSprite()
{
	//========== ANIMATE IMAGE ==========
	CCAnimation *runningAnimation = CCAnimation::create();

	//load the frames of animation
	for (int i = 0; i < 4; i++)
	{
		CCSpriteFrame *frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(i*100, 100, 100, 100));
		runningAnimation->addSpriteFrame(frame);
	}
	//setup animation properties
	runningAnimation->setDelayPerUnit(0.3); // This animation contains 14 frames, will continuous 2.8 seconds.
	runningAnimation->setLoops(10000);
	runningAnimation->setRestoreOriginalFrame(true); // Return to the 1st frame after the 14th frame is played.

	_pRunningAnimate = CCAnimate::create(runningAnimation);

	//start animating the running
	this->runAction(_pRunningAnimate);
}

/*void Character::setupAI(LevelMode levelMode) //TOFIX - Change LevelType to LevelMode
{
	//LevelMode decides which AI to use
}*/

/*!
    @function reduceHealth
    @param		healthReduction:int
				the amount of health to reduce from the cat
    @result		reduces the specified amount of health from the character if it is not immune.
    			if the health reaches 0, sets the state of the cat to be EnumCatState.DEAD
 */
void Character::reduceHealth(int health)
{
	if( !isImmune() )
	{
		_health -= health;

		if(_health <= 0)
			_charState = DEAD;
	}
}

/*!
    @function runUp
    @param		timeDiff:float
				time difference since the last call
    @result		moves the character UP based on its current speed and multiplier.
    			cat moves straight again after moving 1 grid
 */
void Character::runUp(float timeDiff)
{
	float moveAmount = (_speedY * timeDiff) * _speedMultiplier;

	if( canMove(moveAmount) )
	{
		//update position to move towards top of screen based on speed (TOP, MINUS)
		this->setPositionY(this->getPositionY() - moveAmount);
	}
}

/*!
    @function runDown
    @param		timeDiff:float
				time difference since the last call
    @result		moves the character DOWN based on its current speed and multiplier.
    			cat moves straight again after moving 1 grid
 */
void Character::runDown(float timeDiff)
{
	float moveAmount = (_speedY * timeDiff) * _speedMultiplier;

	if( canMove(moveAmount) )
	{
		//update position to move towards bottom of screen based on speed (DOWN, PLUS)
		this->setPositionY(this->getPositionY() + moveAmount);
	}
}

/*!
    @function stop
    @param		timeDiff:float
				time difference since the last call
    @result		character gradually stops before running again
    			remains immune for immunity duration
 */
void Character::stop(float timeDiff)
{
	_speedX -= STOP_SPEED;
	_immunityDuration = BASE_IMMUNITY;

	if(_speedX <= 0)
	{
		_speedX = BASE_SPEED;
		setCharState(RUN);
	}
}

/*!
    @function canMove
    @param		moveAmount: float
				the amount to move on each update call
    @result		move till the character has covered 1 grid
    			then reset _amountMoved and the state to RUN
    			TRUE - character can move up/down
    			FALSE - run straight
 */
bool Character::canMove(float moveAmount)
{
	_amountMoved += moveAmount;

	if( _amountMoved >= _maxMoveDistance)
	{
		_amountMoved = 0;
		setCharState(RUN);
		return false;
	}

	return true;
}

/*!
    @function isImmune
    @result		check if character is immune
 */
bool Character::isImmune()
{
	// Check if char is immune
	if( _immunityDuration <= 0 )
	{
		_immunityDuration = 0;
		return false;
	}

	return true;
}

/*!
    @function update
    @param		timeDiff:float
				time difference between the last update call
    @result		base on the state the character is in, call corresponding functions
 */
void Character::update(float timeDiff)
{
	// Update AI's state if required
	_pCharBaseAI->update(timeDiff);

	// Check if char is immune
	if( isImmune() )
	{
		_immunityDuration -= timeDiff;
	}

	//act according to state
	switch(_charState)
	{
		// play run animation
		case RUN:
			return;

		// Run up 1 grid
		case RUNUP:
			runUp(timeDiff);
			break;

		// Run down 1 grid
		case RUNDOWN:
			runDown(timeDiff);
			break;

		// Stop
		case STOP:
			stop(timeDiff);
			break;

		// Character is dead
		case DEAD:
			return;
	}
}
	
void Character::setPosition(const CCPoint& pos) 
{
	CCSprite::setPosition(pos);
	if (!_nextPosition.equals(pos)) 
	{
		_nextPosition = pos;
	}
}

CCRect Character::getRect()
{
	return CCRectMake(this->getPosition().x - (this->getContentSize().width/2),
						this->getPosition().y - (this->getContentSize().height/2),
						this->getContentSize().width,
						this->getContentSize().height);
}

