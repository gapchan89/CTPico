/*
 *  Map.cpp
 *  Untitled
 *
 *  Created by Guo Wei Tan on 1/20/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */

#include "GameMap.h"
#include "GameManager.h"

//===== CONSTRUCTOR =====
GameMap::GameMap(CCString* pMapImageDirectory, GameManager* screenHolder)
{
	//store reference to canvas
	_screenHolder = screenHolder;

	//store screen size
	_screenSize = CCDirector::sharedDirector()->getWinSize();

	//calculate scale factor for the images
	_scaleFactor = _screenSize.width / BG_IMAGE_WIDTH;

	//calculate the number of pixels per grid (int)
	_pixelsPerGrid = _screenSize.width / SCREEN_GRID_WIDTH;

	//prepare map
	setupMapImage(pMapImageDirectory);
	//prepare obstacles
	setupObstacleImage();

	//add background to display
	screenHolder->addChild(_pBgSprite1, 0);
	screenHolder->addChild(_pBgSprite2, 0);
}

//===== FUNCTIONS =====

/*!
    @function setupObstacleImage
    @result		caches all the obstacle sprites.
    			sets up the obstacle holder and tag counter
 */
void GameMap::setupObstacleImage()
{
	//set up obstacles holder
	_obstacles = new CCArray();

	//initialize obstacle tag count
	_obstacleTagCount = OBSTACLE_IMAGE_TAG;

	//TODO: Caching of obstacles sprites here
	//load obstacle sprites
	//_obstacleSprites = new CCSprite*[];
	//loading of sprites into cache
}


/*!
    @function setupMapImage
    @param		pMapImageDirectory:CCString
				directory of the first background image
    @result		loads the background stated at the directory and directory+1.
    			Also sets up their starting position.
    			Does not add to canvas.
 */
void GameMap::setupMapImage(CCString* pMapImageDirectory)
{
		//actual width
	int imageWidth = BG_IMAGE_WIDTH * _scaleFactor;

	//calculate start and end position of background image
	_bgStartPos = _screenSize.width - imageWidth - imageWidth/2;
	_bgEndPos = _screenSize.width + imageWidth/2;

	//loading background images and add to screen holder
	//TODO: check on directory name and directory name + 1
	_pBgSprite1 = CCSprite::create(pMapImageDirectory->getCString());
	_pBgSprite1->setPosition( ccp( _screenSize.width - imageWidth/2, _screenSize.height/2) ); //first image start within screen
	_pBgSprite1->setScale(_scaleFactor);
	_pBgSprite1->setTag(BG_IMAGE_TAG);

	_pBgSprite2 = CCSprite::create(pMapImageDirectory->getCString());
	_pBgSprite2->setPosition( ccp( _bgStartPos , _screenSize.height/2) ); //second image start outside of screen
	_pBgSprite2->setScale(_scaleFactor);
	_pBgSprite2->setTag(BG_IMAGE_TAG + 1);
}

bool GameMap::checkCollision(CCPoint point)
{
	//TODO: Check whether accurate
	for (int i = 0; i < _obstacles->count(); i++)
	{
		CCSprite* obstacle = (CCSprite*)_obstacles->objectAtIndex(i);
		CCPoint obstaclePoint = obstacle->getPosition();
		//if in same lane
		if (((int)obstaclePoint.y) % _pixelsPerGrid == ((int)point.y) % _pixelsPerGrid)
		{
			//if x position overlaps (distance between 2 points is less than obstacle image width)
			if (obstaclePoint.getDistanceSq(point) < OBSTACLE_IMAGE_WIDTH * OBSTACLE_IMAGE_WIDTH)
				//collided
				return true;
		}
	}
	return false;
}


/*!
    @function getNextGrid
    @param		isObstacle:bool
				whether to spawn an obstacle in the path
	@param		yCoord: float
				the current yCoord the function caller is at
    @result		returns a y coordinate. if isObstacle = true, spawns an obstacle at the y coordinate given
 */
float GameMap::getNextGrid(bool isObstacle, float yCoord)
{
	if (isObstacle)
	{
		//spawn obstacle
		//TODO: change image directory name and randomize obstacle
		CCSprite* obstacleSprite = CCSprite::create("Game/Background/background.jpg");
		obstacleSprite->setPosition( ccp(-_screenSize.width/2 - OBSTACLE_IMAGE_WIDTH/2, yCoord) );
		obstacleSprite->setScale(_scaleFactor);
		obstacleSprite->setTag(_obstacleTagCount++);
		//add to screen
		_screenHolder->addChild(obstacleSprite, 0);
		//add to reference
		_obstacles->addObject(obstacleSprite);

		//return same ycoord as before
		return yCoord; //move straight into obstacle
	}
	else
	{
		//randomize to move up/down/straight
		int direction = arc4random() % 3;

		//return yCoord accordingly
		if (direction == 0) //straight
			return yCoord;
		else if (direction == 1) //up
			return yCoord - _pixelsPerGrid;
		else //down
			return yCoord + _pixelsPerGrid;
	}
}


void GameMap::update(float xSpeed)
{
	xSpeed = 1;

	//update background image position
	_pBgSprite1->setPositionX(_pBgSprite1->getPositionX() + xSpeed);
	_pBgSprite2->setPositionX(_pBgSprite2->getPositionX() + xSpeed);
	//check for scrolling
	if( _pBgSprite1->getPositionX() >= _bgEndPos )
		_pBgSprite1->setPositionX(_bgStartPos);
	if( _pBgSprite2->getPositionX() >= _bgEndPos )
		_pBgSprite2->setPositionX(_bgStartPos);

	//update obstacle
	for (int i = 0; i < _obstacles->count(); i++)
	{
		//update position
		CCSprite* obstacle = (CCSprite*)_obstacles->objectAtIndex(i);
		obstacle->setPositionX(obstacle->getPositionX() + xSpeed);

		//check for out of screen obstacles to be deleted
		if (obstacle->getPositionX() > _screenSize.width/2 + OBSTACLE_IMAGE_WIDTH/2)
		{
			//out of screen
			_screenHolder->removeChildByTag(obstacle->getTag());
			_obstacles->removeObjectAtIndex(i);
			delete obstacle;
			//TODO: check on how CCArray work
			i--;
		}
	}
}

GameMap::~GameMap()
{
	//clear obstacles
	for (int i = 0; i < _obstacles->count(); i++)
	{
		CCSprite* obstacle = (CCSprite*)_obstacles->objectAtIndex(i);
		_screenHolder->removeChildByTag(obstacle->getTag());
		delete obstacle;
	}
	delete[] _obstacles;

	//TODO: delete obstacle sprites cache

	//delete image
	_screenHolder->removeChildByTag(_pBgSprite1->getTag());
	_screenHolder->removeChildByTag(_pBgSprite2->getTag());
	delete _pBgSprite1;
	delete _pBgSprite2;
}

