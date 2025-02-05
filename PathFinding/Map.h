#pragma once
#include "Play.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
#include "Directions.h"
class Map
{
private:
	std::vector<Tile> tiles;
	
	int width, height;
	const int tilesize = 10;
	int stride;
	int offsetX, offsetY;
public:
	Map(const char* filePath);
	~Map();
	void LoadFromFile(const char* filePath);
	void Render(bool finished);
	void RenderOneTile(Tile* tile);
	void DrawLines();

	void SetOffset(int offsetXs, int offsetYs);
	Tile* GetTile(int x, int y);

	Tile* startTile; 
	Tile* goalTile; 
	


	void SetupNeighbors();
};

