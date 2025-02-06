#pragma once
#include "Map.h"
#include <vector>
#include <queue>
#include <map>
class AStar
{
private:
	Map& map;
	float GetDistance(Tile* current, Tile* goal); 
	

	std::map<Tile*,Atile*> closedListMap;
	std::map<Tile*, Atile*> openListMap; 
	Atile* currentAtile;
	
public:

	AStar(Map& thismap);
	~AStar();
	std::vector<Tile*> FindPath(Tile* start, Tile* goal);
	bool finished = false;
	std::vector<Tile*> RetracePath(Atile* end);
};

