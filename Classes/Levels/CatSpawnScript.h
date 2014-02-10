/*
 *  CatSpawnScript.h
 *  
 *
 *  Created by Guo Wei Tan on 1/18/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */

#include "CatSpawnSet.h"
#include "Cats/BaseCat.h"
#include "cocos2d.h"

#ifndef _CAT_SPAWN_SCRIPT_H_
#define _CAT_SPAWN_SCRIPT_H_

using namespace cocos2d;

class CatSpawnScript 
{
private:
	CCArray* _pSpawnSets;
	int		 _currentSet, _prespawnTimer;


public:
	//===== CONSTRUCTOR =====
	CatSpawnScript(CCArray* pSpawnSets=0);
	
	//===== DESTRUCTOR =====
	~CatSpawnScript();

	//===== FUNCTIONS =====
	CCArray* updateAndCheckForSpawns(float timeDiff);

	//===== SETTERS =====
	void addSpawnSet(CatSpawnSet* pNewSet);
};

#endif
