#include "AStar.h"

AStar::AStar(Map& thismap): map(thismap)
{
    currentAtile = nullptr;
}
AStar::~AStar()
{
   
    
}

float AStar::GetDistance(Tile* current, Tile* destination) {
    int dstX = std::abs(current->GetPosition().x - destination->GetPosition().x);
    int dstY = std::abs(current->GetPosition().y - destination->GetPosition().y);

    if (dstX > dstY)
    {
        return 14 * dstY + 10 * (dstX - dstY); 
    }
       
    return 14 * dstX + 10 * (dstY - dstX);
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
        
    }
    
    if (!openListMap.empty())
    {
         currentAtile = openListMap[0];
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

         for (auto a : openListMap)
         {
             if (a.second->fCost() < currentAtile->fCost())
             {
                 currentAtile = a.second;
             }
         }
         openListMap.erase(currentAtile->tile);
         closedListMap[currentAtile->tile] = currentAtile;
         for (Tile* neigbhor: currentAtile->tile->neighbors)
         {
             auto it = closedListMap.find(neigbhor);
             if (it != closedListMap.end())
             {
                 continue; // if neighbor is in closedList
             }
             int newGCost = currentAtile->gCost + GetDistance(currentAtile->tile, neigbhor);
            
         }
       

    }
   
    return std::vector<Tile*>(); 
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