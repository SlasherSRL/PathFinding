#include "RWalk.h"
RWalk::RWalk(Map& thismap): map(thismap)
{
	finished = false;
	currentTile = nullptr;
}
RWalk::~RWalk()
{
	for (auto tile : visited)
	{
		delete tile.second;
	}
	visited.clear(); 
}

std::vector<Tile*> RWalk::FindPath(Tile* start, Tile* goal)
{
	if (finished)
	{
		return std::vector<Tile*>();
	}

	if (currentTile == nullptr)
	{
		currentTile = new DTile();
		currentTile->tile = start;
		currentTile->parent = nullptr;
		currentTile->visited = true;
		currentTile->tile->color = Play::cYellow;
		visited[start] = currentTile;
		return std::vector<Tile*>();
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
	std::vector<Tile*> unvisitedNeighbors;
	for (Tile* neighbor : currentTile->tile->neighbors)
	{
		if (visited.find(neighbor) == visited.end()) // Check if not visited
		{
			unvisitedNeighbors.push_back(neighbor);
		}
	}
	if (!unvisitedNeighbors.empty())
	{
		Tile* nextTile = unvisitedNeighbors[rand() % unvisitedNeighbors.size()];

		// Create new DTile and move there
		DTile* nextDTile = new DTile();
		nextDTile->tile = nextTile;
		nextDTile->parent = currentTile;
		nextDTile->visited = true;
		visited[nextTile] = nextDTile; // Add to map

		currentTile = nextDTile;
		currentTile->tile->color = Play::cYellow;
	}
	else
	{
		currentTile->tile->color = Play::cRed;
		currentTile = currentTile->parent;

		if (currentTile == nullptr)
		{
			// No path found
			finished = true; 
		}
	}
	return std::vector<Tile*>();
}
std::vector<Tile*> RWalk::FindWholePath(Tile* start, Tile* goal)
{
	std::vector<Tile*> path;
	while (!finished)
	{
		path = FindPath(start, goal);
	}
	return path;
}
std::vector<Tile*> RWalk::RetracePath(DTile* end)
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