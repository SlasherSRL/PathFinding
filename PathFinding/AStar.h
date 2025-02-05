#pragma once
#include "Map.h"
#include <vector>
#include <queue>
#include <map>
class AStar
{
private:
	Map& map;
	float GetDistance(std::shared_ptr<Tile> current, std::shared_ptr<Tile> destination);
	

	std::map<std::shared_ptr<Tile>,std::shared_ptr<Atile>> closedListMap;
	std::map<std::shared_ptr<Tile>, std::shared_ptr<Atile>> openListMap;
	std::shared_ptr<Atile> currentAtile; 
	
public:

	AStar(Map& thismap);
	~AStar();
	std::vector<std::shared_ptr<Tile>> FindPath(std::shared_ptr<Tile> start, std::shared_ptr<Tile> goal);
	bool finished = false;
	std::vector<std::shared_ptr<Tile>> RetracePath(std::shared_ptr<Atile> end);
};

