#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Map.h"
#include "AStar.h"
int DISPLAY_WIDTH = 720;
int DISPLAY_HEIGHT = 380;
int DISPLAY_SCALE = 3;

Map map1("../Maps/Map1.txt");

Map map2("../Maps/Map2.txt");
Map map3("../Maps/Map3.txt");

AStar astarMap1(map1);

AStar astarMap2(map2);

AStar astarMap3(map3);
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
	
	
	std::vector<Tile*> path1;
	if (!astarMap1.finished)
	{
		 path1= astarMap1.FindPath(map1.startTile, map1.goalTile);
		 map1.Render(false); 
	}
	if (astarMap1.finished)
	{
		map1.Render(true);
		
	}
	//map1.DrawLines();
	map2.Render(false);
	if (!astarMap2.finished)
	{
		std::vector<Tile*> path = astarMap2.FindPath(map2.startTile, map2.goalTile);
	}
	if (astarMap2.finished)
	{
		map2.Render(true);
	}
	//map2.DrawLines();
	map3.Render(false);
	 if (!astarMap3.finished)
	{
		std::vector<Tile*> path = astarMap3.FindPath(map3.startTile, map3.goalTile);
	}
	if (astarMap3.finished)
	{
		map3.Render(true);
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

