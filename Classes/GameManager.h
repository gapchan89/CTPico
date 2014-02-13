#ifndef __GAMEMANAGER_SCENE_H__
#define __GAMEMANAGER_SCENE_H__

#include "cocos2d.h"

class CCBlade;
class Character;
class GameMap;
class Level;

class LevelLoader;

class GameManager : public cocos2d::CCLayer
{
private:

	enum {
		bPAUSEBUTTON
	};

	Character*						myCharacter;
	//CatsManager*					myCatsManager;
	GameMap*						myMap;
	//Skills*						mySkills;
	Level*							myLevel;
	int								chargePoints;
	int								currentChain;

	//temp - need verify where levelloader belongs to. Flowcontroller?
	LevelLoader*					myLevelLoader;

	//Combo
	bool							comboOn;
	float							comboTimer;
	int								comboCounter;

	//Accelerometer
	double							offsetX, accX;
	double							offsetY, accY;
	bool							skillOn;

	//Cat methods >>TEMP
	cocos2d::CCArray*				myCats;

	//map update variables //TEMP
	//int							bgStartPosX, bgEndPosX, bgWidth;
	//float							bgScale;

	//============================== Update function ==========================
	void 							update(float dt);
	void 							updateComboCounter();

	//====================== Touch functions =====================
    std::map< cocos2d::CCTouch *, CCBlade * >  _map; //For touch swiping effect

    //====================== UI Buttons =====================
    void							pauseButtonPressed(); //For pause button
    void							keyBackClicked(); //For back key button

public:
    //============================= Constructor and Initialistion ====================
	GameManager(void);
	~GameManager(void);
    virtual bool 					init();
    static cocos2d::CCScene* 		scene();
    CREATE_FUNC(GameManager);

    //============================= Level Loading TO BE UPDATED LATER ================
    void							loadGame();

    //============================== Touches Methods ============================
    virtual void 					ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void 					ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void 					ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    //============================== Accelerometer ===============================
    virtual void 					didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);

    //==================================TEMP======================================
    void 							createNewCat();
    void 							removeCat(cocos2d::CCNode* object);

    void 							addCat();
    void							spriteMoveFinished(CCNode* sender);

};

#endif // __GAMEMANAGER_SCENE_H__
