/*
 * LevelLoader.cpp
 *
 *  Created on: Jan 27, 2014
 *      Author: GW
 */

#include "LevelLoader.h"
#include "Level.h"
#include "EnumLevelType.h"
#include "CatSpawnSet.h"
#include "CatSpawnScript.h"
#include "CutScene.h"

//===== CONSTRUCTOR =====
LevelLoader::LevelLoader()
{
	_levelFileDirectory = new CCString("levelFileXMLDirectory.xml");
}
LevelLoader::~LevelLoader()
{
	delete _levelFileDirectory;
}

//===== FUNCTIONS =====

/*!
    @function 	getLevelList
    @result		returns an array of all levels (light-loaded)
 */
Level** LevelLoader::getLevelList()
{
	//load the levels and store into levelList
	CCString levelsFile = CCFileUtils::sharedFileUtils()->fullPathForFilename("Game/Level/Levels.plist");

	CCArray *levelData = CCArray::createWithContentsOfFileThreadSafe(levelsFile.getCString());
	Level** levelList = new Level*[levelData->count()];

	CCLog("Number of levels: %d", levelData->count());

	for( int i = 0 ; i < levelData->count() ; i++ )
	{
		CCDictionary *individuallevelData = (CCDictionary*)levelData->objectAtIndex(i);

		int leveltype = individuallevelData->valueForKey("levelType")->intValue();
		int levelnumber = individuallevelData->valueForKey("levelNumber")->intValue();
		int levelscore = individuallevelData->valueForKey("levelScore")->intValue();
		bool levelcompleted = (individuallevelData->valueForKey("levelComleted"))->boolValue();

		/*CCLog("leveltype: %d", leveltype);
		CCLog("levelnumber: %d", levelnumber);
		CCLog("levelscore: %d", levelscore);
		CCLog("levelcompleted: %d", levelcompleted);*/

		levelList[i] = new Level(leveltype,levelcompleted,levelnumber,levelscore);
	}

	return levelList;
}


/*!
    @function getLevel
    @param		levelNumber:int
				level number to retrieve
    @result		returns a full load level
 */

Level* LevelLoader::getLevel(int levelNumber)
{
	//load the levels and store into levelList
	CCString levelsFile = CCFileUtils::sharedFileUtils()->fullPathForFilename("Game/Level/Levels.plist");

	CCArray *levelData = CCArray::createWithContentsOfFileThreadSafe(levelsFile.getCString());
	Level* levelList = new Level[levelData->count()];

	CCLog("Number of levels: %d", levelData->count());

	//levelNumber must minus 1 if the stage number does not start from 0
	CCDictionary *individuallevelData = (CCDictionary*)levelData->objectAtIndex(levelNumber-1);

	int leveltype = individuallevelData->valueForKey("levelType")->intValue();

	//Array of spawn script. Each script is a CCDictionary
	CCArray* spawnscript = (CCArray*)individuallevelData->valueForKey("spawnScript");
	CatSpawnScript *newscript = NULL;
	if( spawnscript->count() > 0 )
	{
		for( int i = 0 ; i < spawnscript->count() ; i++ )
		{
			//TODO: Convert the data into spawn sets
			CCDictionary *spawnset = (CCDictionary*)spawnscript->objectAtIndex(i);

			int typeofcat = spawnset->valueForKey("typeOfCat")->intValue();
			int spawninterval = spawnset->valueForKey("spawnInterval")->intValue();
			int spawntimer = spawnset->valueForKey("spawnTimer")->intValue();
			int prespawndelay = spawnset->valueForKey("prespawnDelay")->intValue();
			int numbertospawn = spawnset->valueForKey("numberToSpawn")->intValue();

			//TODO: Check why spawntimer is not used
			CatSpawnSet newset(typeofcat,spawninterval,numbertospawn,prespawndelay);
		}
		//Add set to script here
	}

	//CCString cutscene = CCString::create(individuallevelData->valueForKey("cutScene").getCString());//TEMP
	int levelnumber = individuallevelData->valueForKey("levelNumber")->intValue();
	int levelscore = individuallevelData->valueForKey("levelScore")->intValue();
	bool levelcompleted = (individuallevelData->valueForKey("levelComleted"))->boolValue();
	int maxdifficulty = individuallevelData->valueForKey("maxDifficulty")->intValue();
	int mindifficulty = individuallevelData->valueForKey("minDifficulty")->intValue();
	int numofobstacles = individuallevelData->valueForKey("numOfObstacles")->intValue();
	int mapwidth = individuallevelData->valueForKey("mapWidth")->intValue();

	CutScene *tempcutscene;

	CCLog("leveltype: %d", leveltype);
	CCLog("levelnumber: %d", levelnumber);
	CCLog("levelscore: %d", levelscore);
	CCLog("levelcompleted: %d", levelcompleted);
	CCLog("maxdifficulty: %d", maxdifficulty);
	CCLog("mindifficulty: %d", mindifficulty);
	CCLog("numofobstacles: %d", numofobstacles);
	CCLog("mapwidth: %d", mapwidth);

	Level *leveldata = new Level(leveltype,newscript, tempcutscene, levelcompleted,levelnumber,levelscore
			,mindifficulty,maxdifficulty,numofobstacles,mapwidth,_levelFileDirectory);
	return leveldata;
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

}
