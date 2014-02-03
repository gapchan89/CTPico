#ifndef _LEVEL_LOADER_H_
#define _LEVEL_LOADER_H_

/*
*  LevelLoader.h
 *  Untitled
 *
 *  Created by Guo Wei Tan on 1/20/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */
#include "cocos2d.h"

using namespace cocos2d;

class LevelLoader
{
private:
	CCString*	_levelFileDirectory;

public:

	//===== CONSTRUCTOR =====
	LevelLoader();

	//===== FUNCTIONS =====
	Level* getLevelList();
	Level getLevel(int levelNumber);
	void setLevelScore(int levelNumber, int score);
	void setLevelCompleted(int levelNumber, bool completed);


	//===== DESTRUCTOR =====
	~LevelLoader();
};

#endif 
