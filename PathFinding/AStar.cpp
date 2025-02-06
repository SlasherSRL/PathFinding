#include "AStar.h"

AStar::AStar(Map& thismap): map(thismap)
{
    currentAtile = nullptr;
}
AStar::~AStar()
{
   
    for (auto& pair : openListMap) delete pair.second;
    for (auto& pair : closedListMap) delete pair.second;

    openListMap.clear();
    closedListMap.clear();
}

float AStar::GetDistance(Tile* current, Tile* destination) {
    int dstX = std::abs(current->GetPosition().x - destination->GetPosition().x);
    int dstY = std::abs(current->GetPosition().y - destination->GetPosition().y);

    if (dstY < dstX)
    {
        return 14 * dstY + 10 * (dstX - dstY);
    }
    return 14 * dstX + 10 * (dstY - dstX);
    //return 10 * (dstX + dstY) + (14 - 2 * 10) * std::min(dstX, dstY);
}


std::vector<Tile*> AStar::FindPath(Tile* start, Tile*goal)
{
    if (finished)
    {
        return  std::vector<Tile*>();
    }
    if (currentAtile == nullptr)
    {
        currentAtile = new Atile();
        currentAtile->gCost = 0;
        currentAtile->tile = start;
        currentAtile->hCost = GetDistance(currentAtile->tile, goal);
        currentAtile->parent = nullptr;
        openListMap[start] = currentAtile;
        start->color = Play::cYellow;
    }
    
    if (!openListMap.empty())
    {
         
         if (currentAtile->tile == goal)
         {
             finished = true;
             std::vector<Tile*> path = RetracePath(currentAtile);
             for (Tile* tile : path)
             {
                 
                 tile->SetType(TileType::PATH);
             }
             return path;
         }

         Atile* bestTile = nullptr;
         for (const auto& pair : openListMap) {
             if (!bestTile || pair.second->fCost() < bestTile->fCost() ||
                 (pair.second->fCost() == bestTile->fCost() && pair.second->hCost < bestTile->hCost))
             {
                 bestTile = pair.second;
             }
         }

         if (!bestTile)
         {
             return std::vector<Tile*>();
         }

         currentAtile = bestTile;

         openListMap.erase(currentAtile->tile);
         closedListMap[currentAtile->tile] = currentAtile;
         currentAtile->tile->color = Play::cRed;
         for (Tile* neighbor: currentAtile->tile->neighbors)
         {
             auto it = closedListMap.find(neighbor);
             if (it != closedListMap.end())
             {
                 continue; // if neighbor is in closedList
             }
             int newGCost = currentAtile->gCost + GetDistance(currentAtile->tile, neighbor);
             Atile* neighborTile = FindInOpenList(neighbor);
             if (!neighborTile)
             {
                 neighborTile = new Atile();
                 neighborTile->tile = neighbor;
                 openListMap[neighbor] = neighborTile;
                 // Assign gCost and hCost for new tiles
                 neighborTile->gCost = newGCost;
                 neighborTile->hCost = GetDistance(neighbor, goal);
                 neighborTile->parent = currentAtile;
                 neighbor->color = Play::cYellow;
             }
             // If it's already in the open list, check if the path is better
             else if (newGCost < neighborTile->gCost)
             {
                 neighborTile->gCost = newGCost;
                 neighborTile->hCost = GetDistance(neighbor, goal);
                 neighborTile->parent = currentAtile;
                 neighbor->color = Play::cYellow;
             }
             //bool betterPath= false;
             //if (!neighborTile || newGCost < neighborTile->gCost)
             //{
             //    betterPath = true;
             //}
             //if (betterPath)
             //{
             //    if (!neighborTile)
             //    {
             //        neighborTile = new Atile();
             //        neighborTile->tile = neighbor;
             //        openListMap[neighbor] = neighborTile;
             //    }
             //    neighborTile->gCost = newGCost;
             //    neighborTile->hCost = GetDistance(neighbor, goal);
             //    neighborTile->parent = currentAtile;
             //    neighbor->color = Play::cYellow;
             //}
                
             
         }
       

    }
   
    return std::vector<Tile*>(); 
}
std::vector<Tile*> AStar::FindWholePath(Tile* start, Tile* goal)
{
    std::vector<Tile*> path;
    while (!finished)
    {
        path=FindPath(start, goal);
    }
    return path;
}
Atile* AStar::FindInOpenList(Tile* tile)
{
    for (auto& pair : openListMap)
    {
        if (pair.second->tile == tile)
        {
            return pair.second;
        }
    }
    return nullptr;

}

std::vector<Tile*> AStar::RetracePath(Atile* end)
{
    std::vector<Tile*> path;
    Atile* current = end;
    while (current != nullptr)
    {
        path.push_back(current->tile);
        
        current = current->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}