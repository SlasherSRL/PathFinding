#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Map.h"
#include "AStar.h"
#include "Timer.h"
#include "DepthSearch.h"
#include "RWalk.h"
int DISPLAY_WIDTH = 720;
int DISPLAY_HEIGHT = 380;
int DISPLAY_SCALE = 3;

Map map1("../Maps/Map1.txt");

Map map2("../Maps/Map2.txt");
Map map3("../Maps/Map3.txt");

AStar astarMap1(map1);
AStar astarMap2(map2);
AStar astarMap3(map3);

DepthSearch dptMap1(map1);
DepthSearch dptMap2(map2);
DepthSearch dptMap3(map3);

RWalk rWalkMap1(map1);
RWalk rWalkMap2(map2);
RWalk rWalkMap3(map3);


Timer map1Time;

Timer map2Time;

Timer map3Time;


// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	map1.SetOffset(20, 50);
	map2.SetOffset(200, 50);
	map3.SetOffset(400, 50);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cWhite );
	
	Play::DrawDebugText({ 300,350 }, "Currently displaying Depth-first", Play::cBlack);
	//map1
	std::vector<Tile*> path1;
	if (!map1Time.timerStarted)
	{
		map1Time.StartTime();
	}
	if (!dptMap1.finished)
	{
		//map1.Render(false);
		//path1 = dptMap1.FindPath(map1.startTile, map1.goalTile);
		path1 = dptMap1.FindWholePath(map1.startTile, map1.goalTile);
	}
	if (dptMap1.finished)
	{
		if (!map1Time.timerStopped)
		{
			map1Time.StopTime();

		}
		map1.Render(true);
		
		Play::DrawDebugText({ 100,270 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 100,250 }, std::to_string(map1Time.time).c_str(), Play::cBlack);

	}
	if (!astarMap1.finished)
	{
		//map1.Render(false);
		
		 //path1= astarMap1.FindPath(map1.startTile, map1.goalTile);
		//path1 = astarMap1.FindWholePath(map1.startTile, map1.goalTile);
		  
	}
	if (astarMap1.finished)
	{
		if (!map1Time.timerStopped)
		{
			map1Time.StopTime();

		}
		map1.Render(true);

		
		Play::DrawDebugText({ 100,270 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 100,250 }, std::to_string(map1Time.time).c_str(), Play::cBlack);
	}
	if (!rWalkMap1.finished)
	{
		//map1.Render(false);

		//path1= rWalkMap1.FindPath(map1.startTile, map1.goalTile);
		//path1 = rWalkMap1.FindWholePath(map1.startTile, map1.goalTile);

	}
	if (rWalkMap1.finished)
	{
		if (!map1Time.timerStopped)
		{
			map1Time.StopTime();

		}
		map1.Render(true);


		Play::DrawDebugText({ 100,270 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 100,250 }, std::to_string(map1Time.time).c_str(), Play::cBlack);
	}


	//map1.DrawLines();
	
	//map2 
	std::vector<Tile*> path2;
	if (!map2Time.timerStarted)
	{
		map2Time.StartTime();
	}
	if (!dptMap2.finished)
	{
		//map2.Render(false);
		//path2 = dptMap2.FindPath(map2.startTile, map2.goalTile);
		path2 = dptMap2.FindWholePath(map2.startTile, map2.goalTile);
	}
	if (dptMap2.finished)
	{
		if (!map2Time.timerStopped)
		{
			map2Time.StopTime();

		}
		map2.Render(true);
		
		Play::DrawDebugText({ 280,280 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 280,250 }, std::to_string(map2Time.time).c_str(), Play::cBlack);

	}
	if (!astarMap2.finished)
	{
		//map2.Render(false);
		//path2 = astarMap2.FindPath(map2.startTile, map2.goalTile);
		//path2 = astarMap2.FindWholePath(map2.startTile, map2.goalTile);
	}
	if (astarMap2.finished)
	{
		if (!map2Time.timerStopped)
		{
			map2Time.StopTime();

		}
		map2.Render(true);

		
		Play::DrawDebugText({ 280,280 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 280,250 }, std::to_string(map2Time.time).c_str(), Play::cBlack);
	}
	if (!rWalkMap2.finished)
	{
		//map2.Render(false);
		
		//path2= rWalkMap2.FindPath(map2.startTile, map2.goalTile);
		//path2 = rWalkMap2.FindWholePath(map2.startTile, map2.goalTile);

	}
	if (rWalkMap2.finished)
	{
		if (!map2Time.timerStopped)
		{
			map2Time.StopTime();

		}
		map2.Render(true);


		Play::DrawDebugText({ 280,280 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 280,250 }, std::to_string(map2Time.time).c_str(), Play::cBlack);
	}
	//map2.DrawLines();

	//map 3
	std::vector<Tile*> path3;
	if (!map3Time.timerStarted)
	{
		map3Time.StartTime();
	}
	
	if (!dptMap3.finished)
	{
		//map3.Render(false);
		//path3 = dptMap3.FindPath(map3.startTile, map3.goalTile);
		path3 = dptMap3.FindWholePath(map3.startTile, map3.goalTile);
	}
	if (dptMap3.finished)
	{
		if (!map3Time.timerStopped)
		{
			map3Time.StopTime();

		}
		map3.Render(true);
		
		Play::DrawDebugText({ 520,340 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 520,320 }, std::to_string(map3Time.time).c_str(), Play::cBlack);

	}
	if (!astarMap3.finished)
	{
		// map3.Render(false);
		 //path3 = astarMap3.FindPath(map3.startTile, map3.goalTile);
		// path3 = astarMap3.FindWholePath(map3.startTile, map3.goalTile);
	}
	if (astarMap3.finished)
	{
		if (!map3Time.timerStopped)
		{
			map3Time.StopTime();

		}
		map3.Render(true);
		Play::DrawDebugText({ 520,340 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 520,320 },std::to_string(map3Time.time).c_str(), Play::cBlack);
	}
	if (!rWalkMap3.finished)
	{
		//map3.Render(false);

		//path3= rWalkMap3.FindPath(map3.startTile, map3.goalTile);
	   //path3 = rWalkMap3.FindWholePath(map3.startTile, map3.goalTile);

	}
	if (rWalkMap3.finished)
	{
		if (!map3Time.timerStopped)
		{
			map3Time.StopTime();

		}
		map3.Render(true);


		Play::DrawDebugText({ 520,340 }, "Microseconds", Play::cBlack);
		Play::DrawDebugText({ 520,320 }, std::to_string(map3Time.time).c_str(), Play::cBlack);
	}
	//map3.DrawLines();
	Play::PresentDrawingBuffer();
	
	return Play::KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

