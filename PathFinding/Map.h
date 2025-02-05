#pragma once
#include "Play.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
#include <memory>
#include "Directions.h"
class Map
{
private:
	std::vector<std::shared_ptr<Tile>> tiles;
	
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
	std::shared_ptr<Tile> GetTile(int x, int y);

	std::shared_ptr<Tile> startTile;
	std::shared_ptr<Tile> goalTile;
	


	void SetupNeighbors();
};

