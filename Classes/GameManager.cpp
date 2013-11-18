#include "GameManager.h"
#include "SimpleAudioEngine.h"

#include "NinjaCat.h"
#include "Supporting/CCBlade.h"

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

    //Enable touch
    this->setTouchEnabled(true);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameManager::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Catropico! =D", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    this->addChild(pLabel, 1);

    comboCounter = 0;
    CCLabelTTF* pLabel2 = CCLabelTTF::create("0", "Thonburi", 48);
    pLabel2->setTag(30);
    pLabel2->setPosition( ccp(40, size.height - 50) );
    this->addChild(pLabel2, 1);

    loadGame();

    this->schedule(schedule_selector(GameManager::createNewCat),3.0f);
    this->scheduleUpdate();

    return true;
}

void GameManager::loadGame()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//CCSpriteBatchNode *batchnodes = CCSpriteBatchNode::create("Game/Character/character-run.jpg");
	//CCSpriteFrame *frame = CCSpriteFrame::create("Game/Character/character-run.jpg", CCRect(0,0,116,140) );

	CCAnimation *animation = CCAnimation::create();

	// load image file from local file system to CCSpriteFrame, then add into CCAnimation
	// for (int i = 0; i < 2; i++)
	// {
	CCSpriteFrame *frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(0,100,100,100) );
	animation->addSpriteFrame(frame);

	frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(100,100,100,100) );
	animation->addSpriteFrame(frame);

	frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(200,100,100,100) );
	animation->addSpriteFrame(frame);

	frame = CCSpriteFrame::create("Game/Character/human-spritesheet.png", CCRect(300,100,100,100) );
	animation->addSpriteFrame(frame);
	// }

	CCSprite* cSprite = CCSprite::createWithSpriteFrame(frame);
	//CCSprite* cSprite = CCSprite::create("Game/Character/character-run.jpg");
	cSprite->setPosition(  ccp(size.width/2-200, size.height/2-200) );
	cSprite->setTag(99);
	this->addChild(cSprite,1);

	myCats = new CCArray;

	NinjaCat *cat = NinjaCat::gameSpriteWithFile("Game/Cats/ninja-cat.png");
	cat->setPosition(ccp(1000,200));
	this->addChild(cat,1);
	myCats->addObject(cat);

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

	animation->setDelayPerUnit(0.3); // This animation contains 14 frames, will continuous 2.8 seconds.
	animation->setLoops(10000);
	animation->setRestoreOriginalFrame(true); // Return to the 1st frame after the 14th frame is played.

	CCAnimate *action = CCAnimate::create(animation);
	cSprite->runAction(action);  // run action on sprite object

	CCSprite* bgSprite1 = CCSprite::create("Game/Background/background.jpg");
	bgSprite1->setPosition( ccp( 640, size.height/2) );
	bgSprite1->setScale(1.3f);
	bgSprite1->setTag(1000);
	this->addChild(bgSprite1, 0);

	CCSprite* bgSprite2 = CCSprite::create("Game/Background/background.jpg");
	bgSprite2->setPosition( ccp( -640 , size.height/2) );
	bgSprite2->setScale(1.3f);
	bgSprite2->setTag(1001);
	this->addChild(bgSprite2, 0);
}

//Update function
void GameManager::update(float dt)
{
	CCSprite* characterSprite = (CCSprite*)this->getChildByTag(99);
	//characterSprite->setPosition( ccpAdd( characterSprite->getPosition() , ccp(1,1) ));

	CCSprite* bg1Sprite = (CCSprite*)this->getChildByTag(1000);
	CCSprite* bg2Sprite = (CCSprite*)this->getChildByTag(1001);

	bg1Sprite->setPosition( ccpAdd(bg1Sprite->getPosition(),ccp(1,0) ) );
	bg2Sprite->setPosition( ccpAdd(bg2Sprite->getPosition(),ccp(1,0) ) );

	if( bg1Sprite->getPositionX() >= 1920 )
		bg1Sprite->setPositionX(-640);
	if( bg2Sprite->getPositionX() >= 1920 )
		bg2Sprite->setPositionX(-640);

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
	CCPoint charpos = this->getChildByTag(99)->getPosition();

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

	CCSprite* charc = (CCSprite*)this->getChildByTag(99);
	charc->runAction( CCMoveTo::create(1,ccp( rand()%100 + 200 , rand()%200 + 50 )));

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
	CCSprite* characterSprite = (CCSprite*)this->getChildByTag(99);

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

void GameManager::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
