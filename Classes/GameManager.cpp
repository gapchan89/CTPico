#include "GameManager.h"
#include "SimpleAudioEngine.h"

#include "NinjaCat.h"
#include "Supporting/CCBlade.h"

#include "Character/Character.h"
#include "Map/GameMap.h"
#include "Levels/Level.h"
#include "Levels/LevelLoader.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameManager::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameManager *layer = GameManager::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameManager::GameManager()
:myCats(NULL)
{
}

GameManager::~GameManager()
{
	if( myCats )
	{
		myCats->release();
		myCats = NULL;
	}

	delete myMap;
	myMap = NULL;

	delete myLevelLoader;
	myLevelLoader = NULL;

	//TODO: delete character etc
}

// on "init" you need to initialize your instance
bool GameManager::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    //Enable touch and accelerometer
    this->setTouchEnabled(true);
    this->setAccelerometerEnabled(true);

    //Setup game level data
    loadGame();

    //Setup Update functions
    this->schedule(schedule_selector(GameManager::addCat), 1.0f);
    this->setKeypadEnabled(true); //enable for backkey button
    this->scheduleUpdate();

    return true;
}

void GameManager::loadGame()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//================ Levels ==============================================
	myLevelLoader = new LevelLoader();
	//Level **lightlevels = myLevelLoader->getLevelList(); //For Stage Select
	Level* leveldata = myLevelLoader->getLevel(1);

	//================ MAP ====================
	myMap = new GameMap(CCString::create("Game/Background/BG City 1.png"), this);

	//================ Character =================
	CCSpriteFrame *frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(0,100,100,100) );
	myCharacter = Character::gameSpriteWithFrame(frame);
	this->addChild(myCharacter,1);

	//============= Cats =============== to be changed to catsmanager
	myCats = new CCArray;

	//============ UI ================== have to put this else where i think
	//Scrolling background images variables (Image width = 950)
	/*bgScale = size.width / 950; // temp value for uiSprite value
	CCSprite * uiSprite = CCSprite::create("Game/UI/game ui.png");
	uiSprite->setScale(bgScale);
	uiSprite->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(uiSprite, 10);*/

	float UIscalefactor = myMap->getScaleFactor();

	//HP lives


	//Skill bar
	CCSprite * skillbarSprite = CCSprite::create("Game/UI/[UI] Skill Bar - Base.png");
	skillbarSprite->setScale(UIscalefactor);
	skillbarSprite->setPosition(ccp(size.width/2 + (245*UIscalefactor) ,size.height/2 - (258*UIscalefactor)));
	//skillbarSprite->setTag(950);
	this->addChild(skillbarSprite,11);

	//Pause button
	CCSprite * pauseButtonSprite = CCSprite::create("Game/UI/[Button] Pause - Normal.png");
	CCSprite * pauseButtonSpritePressed = CCSprite::create("Game/UI/[Button] Pause - Pressed.png");
	CCMenuItemSprite* pauseButton = CCMenuItemSprite::create(pauseButtonSprite,pauseButtonSpritePressed,this,menu_selector(GameManager::pauseButtonPressed));
	pauseButton->setScale(UIscalefactor);
	pauseButton->setPosition(ccp(size.width/2 + (530*UIscalefactor),size.height/2 + (280*UIscalefactor)));
    CCMenu* gamemenu = CCMenu::create(pauseButton, NULL);
    gamemenu->setPosition(0,0);
	this->addChild(gamemenu,11);

	skillOn = false;
	CCSprite * metSprite = CCSprite::create("Game/UI/meteor-01.png");
	metSprite->setScale(0.3);
	metSprite->setPosition(ccp(size.width-320,50));
	metSprite->setTag(950);
	this->addChild(metSprite,11);

    //================ COMBO ===================
    comboCounter = 0;
    CCLabelTTF* pLabel2 = CCLabelTTF::create("0", "Thonburi", 48);
    pLabel2->setTag(30);
    pLabel2->setPosition( ccp(40, size.height - 50) );
    this->addChild(pLabel2, 1);

}

//Update function
void GameManager::update(float dt)
{
	//============= CHARACTER =================
	//myCharacter->update(dt);

	//============= MAP =====================
	myMap->update(dt);

	//========== Skill ===========
	if( skillOn )
	{
		//Adjust the meteor based on offsetX, offsetY
		CCSprite *met = (CCSprite*)this->getChildByTag(1200);
		CCSprite *crosshair = (CCSprite*)this->getChildByTag(1201);

		CCPoint point = met->getPosition();
		float crosshairY = crosshair->getPositionY();
		met->setPosition(ccp(point.x + ((accX-offsetX)*8) , point.y - 4 ));
		crosshair->setPosition(ccp(point.x + ((accX-offsetX)*8) , crosshairY ));

		/*CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		float maxX = winSize.height - met->getContentSize().width/2;
		float minX = met->getContentSize().width/2;

		float diff = (accX * dt);
		float newX = met->getPosition().x + diff;
		newX = MIN(MAX(newX, minX), maxX);
		met->setPosition(ccp(newX , met->getPosition().y - 4 ));
		crosshair->setPosition(ccp(newX , crosshair->getPosition().y ));*/

		//Init world destruction
		if( point.y < 200 )
		{
			skillOn = false;
			this->removeChildByTag(1200);
			this->removeChildByTag(1201);

			CCObject *cat = NULL;
			CCARRAY_FOREACH(myCats, cat)
			{
				NinjaCat *ncat = dynamic_cast<NinjaCat*>(cat);
				if( !ncat->returnIsDead() )
				{
					ncat->setIsDead(true);

					CCActionInterval* rotate = CCRotateBy::create(0.5f , 150);
					CCAction *act = CCRepeatForever::create(rotate);

					CCSequence* seq = CCSequence::create(
							CCMoveBy::create(1,ccp(500,rand()%300+600)),
							CCCallFuncN::create( this, callfuncN_selector(GameManager::removeCat)),
							NULL
					);

					ncat->runAction(act);
					ncat->runAction(seq);
				}
			}
		}
	}

	//========== COMBO ==========
	if( comboOn )
	{
		comboTimer += dt;
		if( comboTimer > 0.2 )
		{
			comboOn = false;
			comboTimer = 0;
			comboCounter = 0;

			CCObject *cat = NULL;
			CCARRAY_FOREACH(myCats, cat)
			{
				NinjaCat *ncat = dynamic_cast<NinjaCat*>(cat);
				if( ncat->returnIsDead() )
					continue;

				if( ncat->returnIsClicked() )
				{
					ncat->setIsClicked(false);
					ncat->setIsDead(true);

					//ncat->runAction(CCAction::create())
					CCActionInterval* rotate = CCRotateBy::create(0.5f , 150);
					CCAction *act = CCRepeatForever::create(rotate);

					CCSequence* seq = CCSequence::create(
							CCMoveBy::create(1,ccp(500,rand()%300+600)),
							CCCallFuncN::create( this, callfuncN_selector(GameManager::removeCat)),
							NULL
					);

					ncat->runAction(act);
					ncat->runAction(seq);
				}
			}
		}
	}
}

void GameManager::updateComboCounter()
{
	comboCounter++;

    CCLabelTTF* pLabel2 = (CCLabelTTF*)this->getChildByTag(30);

    pLabel2->setString(CCString::createWithFormat("%d",comboCounter)->getCString());
}

void GameManager::createNewCat()
{
	CCPoint charpos = ccp(0,0);//this->getChildByTag(99)->getPosition();

	//Formation
	if( rand()%2 == 0 )
	{
		for( int i = 0 ; i < 3 ; i++ )
		{
			NinjaCat *cat = NinjaCat::gameSpriteWithFile("Game/Cats/ninja-cat.png");
			cat->setPosition(ccp(1000,i*100 +50));

			CCActionInterval* rotate = CCRotateBy::create(0.5f , 150);
			CCAction *act = CCRepeatForever::create(rotate);

			CCSequence* seq = CCSequence::create(
					CCMoveBy::create(4,ccp(-400,0)),
					CCMoveTo::create(1.5,charpos),
					NULL
			);

			cat->runAction(seq);

			this->addChild(cat,1);
			myCats->addObject(cat);
		}

	}
	else
	{
		NinjaCat *cat = NinjaCat::gameSpriteWithFile("Game/Cats/ninja-cat.png");
		cat->setPosition(ccp(1000,rand()%200 + 50));

		cat->runAction(CCMoveTo::create(5,charpos));

		this->addChild(cat,1);
		myCats->addObject(cat);
	}



	//float r = (float)(rand()%4 + 1);
    //this->scheduleOnce(schedule_selector(GameManager::createNewCat),1.0f);
}

void GameManager::removeCat(CCNode* object)
{
	NinjaCat* ncat = dynamic_cast<NinjaCat*>(object);

	ncat->stopAllActions();
	ncat->setVisible(false);

	myCats->removeObject(ncat, true);
}

//Touches methods
void GameManager::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	//Getting count of touches
	//touches->count();

	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

	CCSprite *metSprite = (CCSprite*)this->getChildByTag(950);
	if( metSprite->boundingBox().containsPoint(location) && !skillOn )
	{
		//========= METEOR FALL ===========
		skillOn = true;
		offsetX = accX;
		offsetY = accY;

		CCAnimation *skillAnimation = CCAnimation::create();

		CCSpriteFrame *skillFrame = CCSpriteFrame::create("Game/Skill/meteor.png", CCRect(0, 0,80,94) );
		skillAnimation->addSpriteFrame(skillFrame);

		skillFrame = CCSpriteFrame::create("Game/Skill/meteor.png", CCRect(80, 0,80,94) );
		skillAnimation->addSpriteFrame(skillFrame);

		skillFrame = CCSpriteFrame::create("Game/Skill/meteor.png", CCRect(160, 0,80,94) );
		skillAnimation->addSpriteFrame(skillFrame);

		skillFrame = CCSpriteFrame::create("Game/Skill/meteor.png", CCRect(240, 0,80,94) );
		skillAnimation->addSpriteFrame(skillFrame);

		skillFrame = CCSpriteFrame::create("Game/Skill/meteor.png", CCRect(320, 0,80,94) );
				skillAnimation->addSpriteFrame(skillFrame);

		skillAnimation->setDelayPerUnit(0.1); // This animation contains 14 frames, will continuous 2.8 seconds.
		skillAnimation->setLoops(10000);
		skillAnimation->setRestoreOriginalFrame(true); // Return to the 1st frame after the 14th frame is played.

		CCSprite* meteor = CCSprite::createWithSpriteFrame(skillFrame);
		CCAnimate *action = CCAnimate::create(skillAnimation);
		meteor->runAction(action);  // run action on sprite object

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		meteor->setPosition(ccp(winSize.width/2,winSize.height+100));
		meteor->setTag(1200);

		this->addChild(meteor,9);

		//=========== CROSSHAIR ========
		CCSprite *crosshair = CCSprite::create("Game/Skill/crosshair.png");
		crosshair->setPosition(ccp(winSize.width/2,200));
		crosshair->setTag(1201);

		this->addChild(crosshair,10);
	}

    for (CCSetIterator it = touches->begin(); it != touches->end(); it++) {
        CCTouch *touch = (CCTouch *)*it;
		CCBlade *blade = CCBlade::create("Game/streak.png", 4, 50);
        _map[touch] = blade;
		addChild(blade);

        blade->setColor(ccc3(255,255,255));
        blade->setOpacity(100);
        blade->setDrainInterval(1.0/80);

        CCPoint point = convertTouchToNodeSpace(touch);
		blade->push(point);
	}

    //================= CHARACTER =========================
	//CCSprite* charc = (CCSprite*)this->getChildByTag(99);
	//charc->runAction( CCMoveTo::create(1,ccp( rand()%100 + 200 , rand()%200 + 50 )));

	//================== CATS ==============================
	CCObject *cat = NULL;
	CCARRAY_FOREACH(myCats, cat)
	{
		NinjaCat *ncat = dynamic_cast<NinjaCat*>(cat);
		if( ncat->returnIsDead() )
			continue;

		if( ncat->boundingBox().containsPoint(location) )
		{
			if( !ncat->returnIsClicked() )
			{
				ncat->setIsClicked(true);
				comboTimer = 0;
				updateComboCounter();
			}
		}

		//Move the cat to finger
		//if( ncat->returnIsClicked() )
		//	ncat->setPosition(location);
	}

	if( !comboOn )
	{
		comboOn = true;
		comboTimer = 0;
	}

}

void GameManager::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

    for (CCSetIterator it = touches->begin(); it != touches->end(); it++) {
        CCTouch *touch = (CCTouch *)*it;
        if (_map.find(touch) == _map.end()) continue;

        CCBlade *blade = _map[touch];
        CCPoint point = convertTouchToNodeSpace(touch);
        point = ccpAdd(ccpMult(point, 0.5f), ccpMult(touch->getPreviousLocation(), 0.5f));
		blade->push(point);
    }

	if( !comboOn )
		return;

	CCObject *cat = NULL;
	CCARRAY_FOREACH(myCats, cat)
	{
		NinjaCat *ncat = dynamic_cast<NinjaCat*>(cat);
		if( ncat->returnIsDead() )
			continue;

		if( ncat->boundingBox().containsPoint(location) )
		{
			if( !ncat->returnIsClicked() )
			{
				ncat->setIsClicked(true);
				comboTimer = 0;
				updateComboCounter();
			}
		}

		//Move the cat to finger
		//if( ncat->returnIsClicked() )
		//	ncat->setPosition(location);
	}


}

void GameManager::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);

    for (CCSetIterator it = touches->begin(); it != touches->end(); it++) {
        CCTouch *touch = (CCTouch *)*it;
        if (_map.find(touch) == _map.end()) continue;

        CCBlade *blade = _map[touch];
        blade->autoCleanup();
        _map.erase(touch);
    }
}

void GameManager::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue)
{
      accX = pAccelerationValue->x;                //horizontal acceleration
      accY = pAccelerationValue->y;                //vertical acceleration

      /*
      #define KFILTERINGFACTOR 0.1
	  #define KRESTACCELX -0.6
	  #define KSHIPMAXPOINTSPERSEC (winSize.height*0.5)
	  #define KMAXDIFFX 0.2

      double rollingX;

      pAccelerationValue->y = pAccelerationValue->x;
      rollingX = (pAccelerationValue->y * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
      float accelX = pAccelerationValue->y - rollingX;
      CCSize winSize = CCDirector::sharedDirector()->getWinSize();
      float accelDiff = accelX - KRESTACCELX;
      float accelFraction = accelDiff / KMAXDIFFX;
      accX = KSHIPMAXPOINTSPERSEC * accelFraction;*/

      //CCLog("X: %f   Y: %f",x,y);

      //If you want to move sprite then can use it to change the position..
      //sprite->setPosition(ccp(sprite->getPosition().x+pAccelerationValue->x*3,sprite->getPosition().y));    //I have not tested it but to move sprite horizontally with some speed like x*6..you can change it as accordingly..
}

void GameManager::addCat()
{
	//========== ANIMATE IMAGE ==========
	CCAnimation *catanimation = CCAnimation::create();

	CCSpriteFrame *frame2 = CCSpriteFrame::create("Game/Cats/punk cat.png", CCRect(0, 0,100,100) );
	catanimation->addSpriteFrame(frame2);

	frame2 = CCSpriteFrame::create("Game/Cats/punk cat.png", CCRect(100, 0,100,100) );
	catanimation->addSpriteFrame(frame2);

	frame2 = CCSpriteFrame::create("Game/Cats/punk cat.png", CCRect(200, 0,100,100) );
	catanimation->addSpriteFrame(frame2);

	frame2 = CCSpriteFrame::create("Game/Cats/punk cat.png", CCRect(300, 0,100,100) );
	catanimation->addSpriteFrame(frame2);

	catanimation->setDelayPerUnit(0.2); // This animation contains 14 frames, will continuous 2.8 seconds.
	catanimation->setLoops(10000);
	catanimation->setRestoreOriginalFrame(true); // Return to the 1st frame after the 14th frame is played.

	//========== CALCULATE MOVEMENT ==========

	CCPoint charpos = ccp(0,0);//this->getChildByTag(99)->getPosition();

	//NinjaCat *cat = NinjaCat::gameSpriteWithFile("Game/Cats/ninja-cat.png");
	CCSpriteFrame *frame = CCSpriteFrame::create("Game/Cats/punk cat.png", CCRect(0, 0,100,100) );
	NinjaCat* cat = NinjaCat::gameSpriteWithFrame(frame);

	CCAnimate *action = CCAnimate::create(catanimation);
	cat->runAction(action);

	// Determine where to spawn the target along the Y axis
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = cat->getContentSize().height/2;
	int maxY = winSize.height - 170 - cat->getContentSize().height/2;	// -170 for estimated building height
	int rangeY = maxY - minY;
	// srand( TimGetTicks() );
	int actualY = ( rand() % rangeY ) + minY;

	// Create the target slightly off-screen along the right edge,
	// and along a random position along the Y axis as calculated
	cat->setPosition(ccp(winSize.width + (cat->getContentSize().width/2), actualY) );
	this->addChild(cat, 1);
	myCats->addObject(cat);

	// Determine speed of the target
	int minDuration = (int)3.0;
	int maxDuration = (int)5.0;
	int rangeDuration = maxDuration - minDuration;

	// srand( TimGetTicks() );
	int actualDuration = ( rand() % rangeDuration ) + minDuration;

	// Create the actions
	CCFiniteTimeAction* actionMoveBy = CCMoveBy::create( (float)actualDuration, ccp(-650,0) );
	CCFiniteTimeAction* actionMove = CCMoveTo::create( 1.5, charpos );
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(GameManager::spriteMoveFinished));
	cat->runAction( CCSequence::create(actionMoveBy, actionMove, actionMoveDone, NULL) );
}

// cpp with cocos2d-x
void GameManager::spriteMoveFinished(CCNode* sender)
{
  CCSprite *sprite = (CCSprite *)sender;
  this->removeChild(sprite, true);
}

//===================UI Buttons===============
void GameManager::pauseButtonPressed()
{

}
void GameManager::keyBackClicked()
{
	CCDirector::sharedDirector()->end();

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}








/// USELESS CODE HERE FOR RFERENCE
 	/*NinjaCat *cat = NinjaCat::gameSpriteWithFile("Game/Cats/ninja-cat.png");
	cat->setPosition(ccp(1000,200));
	this->addChild(cat,1);
	myCats->addObject(cat);*/

	//Spam cats
	/*CCSprite* catsprite = CCSprite::create("Game/Cats/ninja-cat.png");
	catsprite->setPosition(  ccp(size.width/2+200,300) );
	this->addChild(catsprite,1);

	CCSprite* catsprite2 = CCSprite::create("Game/Cats/ninja-cat.png");
	catsprite2->setPosition(  ccp(size.width/2+250,250) );
	// catsprite2->setScale(1.5);
	this->addChild(catsprite2,1);

	CCSprite* catsprite3 = CCSprite::create("Game/Cats/ninja-cat.png");
	catsprite3->setPosition(  ccp(size.width/2+330,200) );
	//catsprite3->setScale(0.7);
	this->addChild(catsprite3,1);

	CCSprite* catsprite4 = CCSprite::create("Game/Cats/ninja-cat.png");
	catsprite4->setPosition(  ccp(size.width/2+400,100) );
	//catsprite4->setScale(0.4);
	this->addChild(catsprite4,1);*/
