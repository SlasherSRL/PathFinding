#include "AStar.h"
AStar::AStar(Map& thismap): map(thismap)
{
	
}

float AStar::CalculateHCost(Tile* current, Tile* goal)
{
    int dx = abs(current->GetPosition().x - goal->GetPosition().x);
    int dy = abs(current->GetPosition().y - goal->GetPosition().y);

   
    return std::max(dx, dy);
}

float AStar::GetMovementCost(Tile* current, Tile* next)
{
      // Check if diagonal move
    if (current->GetPosition().x != next->GetPosition().x && current->GetPosition().y != next->GetPosition().y)
    {
        return 14; // Diagonal cost
    }
    else
    {
        return 10; // Straight cost
    }
}

std::vector<Tile*> AStar::FindPath(Tile* start, Tile* goal)
{
    std::vector<Atile> openList;
    std::vector<Atile> closedList;

    Atile startTile;
    startTile.tile = start;
    startTile.parent = nullptr;
    startTile.gCost = 0;
    startTile.hCost = CalculateHCost(start, goal);
    return std::vector<Tile*>();
}