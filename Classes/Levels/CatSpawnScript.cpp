/*
 *  CatSpawnScript.cpp
 *  
 *
 *  Created by Guo Wei Tan on 1/18/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */

#include "CatSpawnScript.h"

//===== CONSTRUCTOR =====
CatSpawnScript::CatSpawnScript(CCArray* pSpawnSets)
{
	_currentSet = 0;
	_prespawnTimer = 0;

	//initialize array if none given
	if (pSpawnSets == 0)
		_pSpawnSets = new CCArray();
	else
		_pSpawnSets = pSpawnSets;
}

//===== DESTRUCTOR =====
CatSpawnScript::~CatSpawnScript()
{
	CCObject* catSpawnSet = 0;
	CCARRAY_FOREACH(_pSpawnSets, catSpawnSet)
	{
		CatSpawnSet* pSpawnSet = dynamic_cast<CatSpawnSet*>(catSpawnSet);
		delete pSpawnSet;
	}

	_pSpawnSets->release();
	delete _pSpawnSets;
}


//===== FUNCTIONS =====
/*!
    @function updateAndCheckForSpawns
    @param		timeDiff:float
				time difference since the last call
    @result		returns a CCArray of CCInteger, each representing a cat type to spawn
 */
CCArray* CatSpawnScript::updateAndCheckForSpawns(float timeDiff)
{
	_prespawnTimer -= timeDiff * 1000;

	//counts prespawn delay and decides when to move to next set
	while (_prespawnTimer <= 0 && _currentSet + 1 < _pSpawnSets->count())
	{
		_currentSet++;
		//retrieve next set
		CatSpawnSet* pSpawnSet = dynamic_cast<CatSpawnSet*>(_pSpawnSets->objectAtIndex(_currentSet));
		//get the prespawn timer
		_prespawnTimer = pSpawnSet->getPreSpawnDelay();
	}


	CCArray* newSpawnsInt = new CCArray();

	//loop through all sets to check if need to spawn new cat
	//loop through all the sets till current set
	for (int i = 0; i < _currentSet; i++)
	{
		CatSpawnSet* pSpawnSet = dynamic_cast<CatSpawnSet*>(_pSpawnSets->objectAtIndex(i));
		//reduce spawn timer and check if ready to spawn
		if (pSpawnSet->reduceSpawnTimer(timeDiff*1000))
			//create a new cat and add to spawn list
			newSpawnsInt->addObject( new CCInteger(pSpawnSet->getTypeOfCat()));
	}

	return newSpawnsInt;
}

//===== SETTERS =====
/*!
    @function addSpawnSet
    @param		pNewSet:CatSpawnSet*
				new set to add into this script
    @result		adds the CatSpawnSet to the end of this script
 */
void CatSpawnScript::addSpawnSet(CatSpawnSet* pNewSet)
{
	_pSpawnSets->addObject(pNewSet);
}

