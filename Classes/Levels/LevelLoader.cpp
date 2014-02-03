/*
 * LevelLoader.cpp
 *
 *  Created on: Jan 27, 2014
 *      Author: GW
 */

#include "LevelLoader.h"

//===== CONSTRUCTOR =====
LevelLoader::LevelLoader()
{
	_levelFileDirectory = new CCString("levelFileXMLDirectory.xml");
}

//===== FUNCTIONS =====

/*!
    @function getLevelList
    @result		returns an array of all levels (light-loaded)
 */
Level* LevelLoader::getLevelList()
{
	Level* levelList = new Level[10];
	//TODO:
	//load the levels and store into levelList

	return levelList;
}


/*!
    @function getLevel
    @param		levelNumber:int
				level number to retrieve
    @result		returns a full load level
 */

Level LevelLoader::getLevel(int levelNumber)
{
	//TODO:
}


/*!
    @function setLevelScore
    @param		levelNumber:int
				level number of level to edit
	@param		score:int
				score to record into the xml file
    @result		records into the xml file the score of the indicated level
 */

void LevelLoader::setLevelScore(int levelNumber, int score)
{
	//TODO:
}


/*!
    @function setLevelCompleted
    @param		levelNumber:int
				level number of level to edit
	@param		completed:boolean
				whether the indicated level is completed
    @result		records into the xml file the completed status of the indicated level
 */

void LevelLoader::setLevelCompleted(int levelNumber, bool completed)
{
	//TODO:
}
