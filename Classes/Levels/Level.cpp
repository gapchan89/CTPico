/*
 *  Level.cpp
 *  
 *
 *  Created by Guo Wei Tan on 1/17/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */

#include "Level.h"

//===== CONSTRUCTOR =====
//for non-light load
/*Level::Level(EnumLevelType levelMode,
			 CatSpawnScript* pSpawnscript,
			 CutScene*	pCutScene,
			 bool levelCompleted,
			 int levelNumber,
			 int levelScore,
			 int minDifficulty,
			 int maxDifficulty,
			 int numOfObstacles,
			 int mapWidth
			 CCString* pMapImageDirectory) 
{
	_lightLoad = false; //automatically false 
	
	_levelMode = levelMode;
	_pSpawnScript = pSpawnscript;
	_pCutScene = pCutScene;
	_levelCompleted = levelCompleted;
	_levelNumber = levelNumber;
	_levelScore = levelScore;
	_minDifficulty = minDifficulty;
	_maxDifficulty = maxDifficulty;
	_numOfObstacles = numOfObstacles;
	_mapWidth = mapWidth;
	_pMapImageDirectory = pMapImageDirectory;
	
}

//light load
Level::Level(EnumLevelType levelMode,
			 bool levelCompleted,
			 int levelNumber,
			 int levelScore)
{
	_lightLoad = true; //automatically true
	
	_levelMode = levelMode;
	_levelCompleted = levelCompleted;
	_levelNumber = levelNumber;
	_levelScore = levelScore;
}*/

Level::Level()
{

}

Level::~Level()
{

}
