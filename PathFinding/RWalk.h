#pragma once
#include "Map.h"
#include <vector>
#include <map> 
class RWalk // random walk
{
private:
	Map& map;

	DTile* currentTile;
	std::map<Tile*, DTile*> visited;

public:

	RWalk(Map& thismap);
	~RWalk();


	std::vector<Tile*> FindPath(Tile* start, Tile* goal);
	std::vector<Tile*> FindWholePath(Tile* start, Tile* goal);
	std::vector<Tile*> RetracePath(DTile* end);


	bool finished;
};

