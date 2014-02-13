/*
 *  CatSpawnSet.cpp
 *  
 *
 *  Created by Guo Wei Tan on 1/17/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */

#include "CatSpawnSet.h"

//===== CONSTRUCTOR =====
CatSpawnSet::CatSpawnSet(int typeOfCat, int spawnInterval, int numberToSpawn, int prespawnDelay)
{
	_typeOfCat = typeOfCat;
	_spawnInterval = spawnInterval;
	_spawnTimer = 0;
	_prespawnDelay = prespawnDelay;
	_numberToSpawn = numberToSpawn;
}

//===== FUNCTIONS =====

/*!
    @function CatSpawnSet
    @param		timeLapse:int		
				time lapsed since the previous call to this function
    @result		returns true if this Cat set is ready to spawn, else returns false.
				This function reduces/resets the spawn timer and spawn counter automatically based on time lapse.
 */

bool CatSpawnSet::reduceSpawnTimer(int timeLapse)
{
	//no more cats to spawn
	if (_numberToSpawn <= 0)
		return false;
	
	//first spawn check
	if (_spawnTimer != 0)
		_spawnTimer -= timeLapse;
	
	//not time to spawn yet
	if (_spawnTimer > 0)
		return false;

	//excess time lapsed overflow to new interval
	_spawnTimer = _spawnInterval + _spawnTimer;
	_numberToSpawn--;
	return true;
}
