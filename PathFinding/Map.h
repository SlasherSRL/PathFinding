#pragma once
#include "Play.h"
#include "Tile.h"
#include <fstream>
#include <iostream>

class Map
{
private:
	std::vector<Tile> tiles;
	int width, height;
	const int tilesize = 30;
public:
	Map(const char* filePath);
	void LoadFromFile(const char* filePath);
	void Render();
	Tile* GetTile(int x, int y);
	void SetupNeighbors();
};

