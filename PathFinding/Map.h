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
public:
	Map(const char* filePath);
	~Map();
	void LoadFromFile(const char* filePath);
	void Render(int offsetX,int offsetY);
	void DrawLines(int offsetX,int offsetY);
	Tile* GetTile(int x, int y);

	
	


	void SetupNeighbors();
};

