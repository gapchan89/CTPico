/*
 *  CatSpawnScript.h
 *  
 *
 *  Created by Guo Wei Tan on 1/18/14.
 *  Copyright 2014 Catropico. All rights reserved.
 *
 */

#include "CatSpawnSet.h"

#ifndef _CAT_SPAWN_SCRIPT_H_
#define _CAT_SPAWN_SCRIPT_H_

class CatSpawnScript 
{
private:
	CatSpawnSet**	_ppSpawnSets;
	int				_currentSet, _totalNumSets;

public:
	//===== CONSTRUCTOR =====
	CatSpawnScript(int totalNumSets, CatSpawnSet** ppSpawnSets = 0);
	
	//===== DESTRUCTOR =====
	~CatSpawnScript();

	//===== SETTERS =====
	void setSpawnSet(CatSpawnSet* pNewSet, int index);
	
	//===== GETTERS =====
	CatSpawnSet* getNextSet();
	CatSpawnSet* getCurrentSet();
	CatSpawnSet* getSet(int index);
	
};

#endif
