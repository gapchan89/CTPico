#ifndef _LEVEL_H_
#define _LEVEL_H_

/*
 *  Level.h
 *  
 *
 *  Created by Guo Wei Tan on 1/17/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */
#include "cocos2d.h"

using namespace cocos2d;

class CatSpawnScript;
class CutScene;

class Level
{

private:
	int	_levelType;
	CatSpawnScript* _pSpawnScript;
	CutScene*		_pCutScene;
	bool			_levelCompleted,
					_lightLoad;
	int				_levelNumber, _levelScore, 
					_minDifficulty, _maxDifficulty,
					_numOfObstacles, _mapWidth;
	CCString*		_pMapImageDirectory;

public:
	//===== CONSTRUCTOR =====
	Level();
	//for non-light load
	Level(	int	levelType,
			CatSpawnScript* pSpawnscript,
			CutScene* 		pCutScene,
			bool 			levelCompleted,
			int 			levelNumber,
			int 			levelScore,
			int 			minDifficulty,
			int 			maxDifficulty,
			int 			numOfObstacles,
			int 			mapWidth,
			CCString* 		pMapImageDirectory);

	//light load
	Level(	int levelType,
			bool levelCompleted,
			int levelNumber,
			int levelScore);

	//===== DESTRUCTOR =====
	~Level();

	//===== SETTERS =====
	void setlevelType(int levelType) { _levelType = levelType; }
	void setSpawnScript(CatSpawnScript* pSpawnScript) { _pSpawnScript = pSpawnScript; }
	void setCutScene(CutScene* pCutScene) { _pCutScene = pCutScene; }
	void setLevelCompleted(bool levelCompleted) { _levelCompleted = levelCompleted; }
	void setLightLoad(bool lightLoad) { _lightLoad = lightLoad; }

	//===== GETTERS =====
	int getLevelType() { return _levelType; }
	CatSpawnScript* getSpawnScript() { return _pSpawnScript; }
	CutScene* getCutScene() { return _pCutScene; }

	bool isLevelCompleted() { return _levelCompleted; }
	bool isLightLoad() { return _lightLoad; }

	int getLevelNumber() { return _levelNumber; }
	int getLevelScore() { return _levelScore; }
	int getMinDifficulty() { return _minDifficulty; }
	int getMaxDifficulty() { return _maxDifficulty; }
	int getNumObstacles() { return _numOfObstacles; }
	int getMapWidth() { return _mapWidth; }

	CCString* getImageDirectory() { return _pMapImageDirectory; }
};

#endif
