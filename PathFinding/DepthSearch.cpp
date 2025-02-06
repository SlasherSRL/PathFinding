#include "DepthSearch.h"
DepthSearch::DepthSearch(Map& thismap) : map(thismap)
{
	currentTile = nullptr;
};

DepthSearch::~DepthSearch()
{
	for (DTile* tile : visited)
	{
		delete tile;
	}
	visited.clear();
}

std::vector<Tile*> DepthSearch::FindPath(Tile* start, Tile* goal)
{
	if (finished)
	{
		return  std::vector<Tile*>();
	}
	if (currentTile == nullptr)
	{
		currentTile = new DTile();
		currentTile->tile = start;
		currentTile->parent = nullptr;
		currentTile->tile->color = Play::cYellow;
		return  std::vector<Tile*>();
	}
	if (currentTile->tile == goal)
	{
		finished = true;
		std::vector<Tile*> path = RetracePath(currentTile);
		for (Tile* tile : path)
		{

			tile->SetType(TileType::PATH);
		}
		return path;
	}
	for (Tile* neighbor : currentTile->tile->neighbors)
	{
		/*if (currentTile->parent!=nullptr)
		{
			if (neighbor == currentTile->parent->tile)
			{
				continue;
			}
			
		}*/
		int count=0;
		for (DTile* tile : visited)
		{
			if (tile->tile = neighbor)
			{
				count = 1;
				break;
			}
			else
			{
				count = 0;
			}
		}
		if (count == 0)
		{
			DTile* neighborTile = new DTile();
			neighborTile->parent = currentTile;
			neighborTile->tile = neighbor;
			
			currentTile = neighborTile;
			currentTile->tile->color = Play::cYellow;
			return  std::vector<Tile*>();
		}
		else
		{
			
			continue;
		}


	}
	visited.push_back(currentTile); 
	currentTile->tile->color = Play::cRed;
	currentTile = currentTile->parent;
	return  std::vector<Tile*>();

}
std::vector<Tile*> DepthSearch::FindWholePath(Tile* start, Tile* goal)
{
	std::vector<Tile*> path;
	while (!finished)
	{
		path = FindPath(start, goal);
	}
	return path;
}

std::vector<Tile*> DepthSearch::RetracePath(DTile* end)
{
	std::vector<Tile*> path;
	DTile* current = end;
	while (current != nullptr)
	{
		path.push_back(current->tile);

		current = current->parent;
	}
	std::reverse(path.begin(), path.end());
	return path;
}