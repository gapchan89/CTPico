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
CatSpawnScript::CatSpawnScript(int totalNumSets, CatSpawnSet** ppSpawnSets)
{
	_currentSet = -1;
	_totalNumSets = totalNumSets;
	
	//initialize array if none given
	if (ppSpawnSets == 0)
		_ppSpawnSets = new CatSpawnSet*[totalNumSets];
	else
		_ppSpawnSets = ppSpawnSets;
}

//===== DESTRUCTOR =====
CatSpawnScript::~CatSpawnScript()
{
	for (int i = 0; i < _totalNumSets; i++)
		delete _ppSpawnSets[i];

	delete[] _ppSpawnSets;
}

//===== SETTERS =====
void CatSpawnScript::setSpawnSet(CatSpawnSet* pNewSet, int index)
{
	if (index >= 0 && index < _totalNumSets)
		_ppSpawnSets[index] = pNewSet;
}

//===== GETTERS =====
CatSpawnSet* CatSpawnScript::getNextSet()
{	
	if (_currentSet + 1 < _totalNumSets)
		return _ppSpawnSets[++_currentSet];
	
	return 0;
}

CatSpawnSet* CatSpawnScript::getCurrentSet()
{
	if (_currentSet >= 0 && _currentSet < _totalNumSets)
		return _ppSpawnSets[_currentSet];
	
	return 0;
}

CatSpawnSet* CatSpawnScript::getSet(int index)
{
	if (index >= 0 && index < _totalNumSets)
		return _ppSpawnSets[index];
	
	return 0;
}
