#ifndef _MAP_H_
#define _MAP_H

/*
*  Map.h
 *  Untitled
 *
 *  Created by Guo Wei Tan on 1/20/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */
#include "cocos2d.h"

class GameManager;

using namespace cocos2d;

class GameMap
{
private:
	const static int MAP_GRID_WIDTH = 500; //whole map
	const static int MAP_GRID_HEIGHT = 5;
	const static int SCREEN_GRID_WIDTH = 50; //on screen

	const static int BG_IMAGE_TAG = 1000;
	const static int BG_IMAGE_WIDTH = 950;

	const static int OBSTACLE_IMAGE_TAG = 2000;
	const static int OBSTACLE_IMAGE_WIDTH = 20;


	GameManager* _screenHolder;
	CCSize		_screenSize;
	float 		_scaleFactor;
	int			_bgStartPos, _bgEndPos, _obstacleTagCount, _pixelsPerGrid;
	CCSprite*	_pBgSprite1;
	CCSprite*	_pBgSprite2;
	CCSprite** 	_obstacleSprites;
	CCArray*	_obstacles;
	
	void setupObstacleImage();
	void setupMapImage(CCString* imageDirectory);

public:

	//===== CONSTRUCTOR =====
	GameMap(CCString* pMapImageDirectory, GameManager* screenHolder);
	
	//===== DESTRUCTOR =====
	~GameMap();

	//===== FUNCTIONS =====
	void update(float xSpeed);
	bool checkCollision(CCPoint point);
	float getNextGrid(bool isObstacle, float yCoord);
	

	//===== GETTERS =====
	float getScaleFactor(){return _scaleFactor;}
};

#endif 
