/*
 *  CatSpawnSet.h
 *  
 *
 *  Created by Guo Wei Tan on 1/17/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */

#ifndef _CAT_SPAWN_SET_H_
#define _CAT_SPAWN_SET_H_

#include "cocos2d.h"

using namespace cocos2d;

class CatSpawnSet: public CCObject
{
private:
	int	_typeOfCat,
		_spawnInterval, //original value 
		_spawnTimer,	//actual timer
		_prespawnDelay, //delay before spawn starts
		_numberToSpawn;
	
public:
	//===== CONSTRUCTOR =====
	CatSpawnSet(int typeOfCat, int spawnInterval, int numberToSpawn, int prespawnDelay = 0);
	
	bool reduceSpawnTimer(int timeLapse);
	
	//===== GETTERS =====
	int getTypeOfCat() { return _typeOfCat; };
	int getNumberToSpawn() { return _numberToSpawn; };
	int getPreSpawnDelay() { return _prespawnDelay; };
};


#endif
