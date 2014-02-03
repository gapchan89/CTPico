#include "EnumLevelType.h"
#include "Map/GameMap.h"
#include "Character.h"

//#include "SimpleAudioEngine.h"

using namespace cocos2d;
//using namespace CocosDenshion;

//===== CONSTRUCTOR =====
Character::Character()
{

}

Character::Character(GameMap* map)
{
	// new CharAI(this, map)
	//charBaseAI;			// AI class to decide on actions
	/*
	setupAI();
	setupSprite();

	speedX = 1;
	speedY = 1;
	health = 3;
	immunityDuration = 2000;
	obstacleHitChance = 10;*/
	
	_vector = ccp(0,0);
}

//===== DESTRUCTOR =====
Character::~Character(void)
{

}

//===== FUNCTIONS =====
Character* Character::gameSpriteWithFrame(CCSpriteFrame *frame)
{
	Character *c = new Character();

	if( c && c->initWithSpriteFrame(frame) )
	{
		c->setupSprite();
		c->autorelease();
		return c;
	}

	CC_SAFE_DELETE(c);
	return NULL;
}

void Character::setupSprite()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCAnimation *animation = CCAnimation::create();

	CCSpriteFrame *frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(0,100,100,100) );
	animation->addSpriteFrame(frame);

	frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(100,100,100,100) );
	animation->addSpriteFrame(frame);

	frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(200,100,100,100) );
	animation->addSpriteFrame(frame);

	frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(300,100,100,100) );
	animation->addSpriteFrame(frame);

	//this->setPosition(  ccp(size.width/2-200, size.height/2-200) );
	this->setTag(99);

	animation->setDelayPerUnit(0.3); // This animation contains 14 frames, will continuous 2.8 seconds.
	animation->setLoops(10000);
	animation->setRestoreOriginalFrame(true); // Return to the 1st frame after the 14th frame is played.

	CCAnimate *action = CCAnimate::create(animation);
	this->runAction(action);
}

//void Character::setupAI(LevelMode levelMode) //TOFIX - Change LevelType to LevelMode
//{
	// LevelMode decides which AI to use
//}

bool Character::reduceHealth(int health)
{
	_health -= health;
	
	if(_health <= 0)
		return false;
	
	return true;
}

void Character::update(float timeDiff)
{
	// CharAI.update(timeDiff)
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

