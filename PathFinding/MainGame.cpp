#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Map.h"
int DISPLAY_WIDTH = 720;
int DISPLAY_HEIGHT = 380;
int DISPLAY_SCALE = 3;

Map map1("../Maps/Map1.txt");
Map map2("../Maps/Map2.txt");
Map map3("../Maps/Map3.txt");

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cWhite );
	map1.Render(20,50);
	map1.DrawLines(20, 50);
	map2.Render(200,50);
	map2.DrawLines(200, 50);
	map3.Render(400,50);
	map3.DrawLines(400, 50);
	Play::PresentDrawingBuffer();
	return Play::KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

