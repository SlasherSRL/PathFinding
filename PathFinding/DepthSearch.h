#pragma once
#include "Map.h"
#include <vector>
class DepthSearch
{
private:
	Map& map;
	std::vector<DTile*> visited; 
	DTile* currentTile;

public:
	DepthSearch(Map& thismap);
	~DepthSearch();


	std::vector<Tile*> FindPath(Tile* start, Tile* goal);
	std::vector<Tile*> FindWholePath(Tile* start, Tile* goal); 
	std::vector<Tile*> RetracePath(DTile* end);


	bool finished = false; 
	 
};

