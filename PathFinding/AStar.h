#pragma once
#include "Map.h"
#include <vector>
class AStar
{
private:
	Map& map;
	float CalculateHCost(Tile* current, Tile* goal); 
	float GetMovementCost(Tile* current, Tile* next);

public:

	AStar(Map& thismap);
	std::vector<Tile*> FindPath(Tile* start, Tile* goal);

};

