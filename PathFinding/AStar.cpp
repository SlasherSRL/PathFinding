#include "AStar.h"

AStar::AStar(Map& thismap): map(thismap)
{
    currentAtile = nullptr;
}
AStar::~AStar()
{
    for (auto& pair : openListMap)
    {
        delete pair.second;
    }
}
//float AStar::CalculateHCost(Tile* current, Tile* goal)
//{
//    int dx = std::abs(current->GetPosition().x - goal->GetPosition().x);
//    int dy = std::abs(current->GetPosition().y - goal->GetPosition().y);
//
//   
//    return std::sqrt(dx * dx + dy * dy);
//}
float AStar::GetDistance(Tile* current, Tile* destination) {
    int dstX = std::abs(current->GetPosition().x - destination->GetPosition().x);
    int dstY = std::abs(current->GetPosition().y - destination->GetPosition().y);

    if (dstX > dstY)
    {
        return 14 * dstY + 10 * (dstX - dstY); 
    }
       
    return 14 * dstX + 10 * (dstY - dstX);
}
//float AStar::GetMovementCost(Tile* current, Tile* next)
//{
//      // Check if diagonal move
//    if (current->GetPosition().x != next->GetPosition().x && current->GetPosition().y != next->GetPosition().y)
//    {
//        return 14; // Diagonal cost
//    }
//    else
//    {
//        return 10; // Straight cost
//    }
//}

std::vector<Tile*> AStar::FindPath(Tile* start, Tile* goal)
{
    if (finished)
    {
        return std::vector<Tile*>();
    }
    if (currentAtile == nullptr) // currentTile is nullptr, set currentTile to startTile
    {
        currentAtile = new Atile();
        currentAtile->tile = start;
        currentAtile->parent = nullptr;
        currentAtile->gCost = 0;
        currentAtile->hCost = GetDistance(start,goal);
         
        openList.push(currentAtile);
        currentAtile->tile->color = Play::cYellow; 
        openListMap[start] = currentAtile; 

    }
    

    if(!openList.empty())
    {
        Atile* currentAtile = openList.top(); 
        openList.pop(); 

        Tile* currentTile = currentAtile->tile; 
        if (currentTile == goal) 
        {
            finished = true;
            std::vector<Tile*> path = RetracePath(currentAtile); 
            for (Tile* tile : path) 
            { 
                tile->SetType(TileType::PATH); // Path tiles are green 
            }
            return path;
        }
        closedList.push_back(currentTile); 
        currentTile->color = Play::cRed;
        for (Tile* neighbor : currentTile->neighbors) 
        {
            if (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) // if neighbor is in closed list
            {
                continue;
            }
            float calcedGCost = currentAtile->gCost + GetDistance(currentTile, neighbor);
            Atile* openAtile = openListMap[neighbor];

            if (openAtile == nullptr) // if Atile doesnt exist for this neighbor
            {
                Atile* newAtile = new Atile();
                newAtile->tile = neighbor;
                newAtile->gCost = calcedGCost;
                newAtile->hCost = GetDistance(neighbor, goal);
                newAtile->parent = currentAtile;
                neighbor->color = Play::cYellow;
                openList.push(newAtile);

                openListMap[neighbor] = newAtile;
            }
            else if( calcedGCost<openAtile->gCost)
            {
                openAtile->gCost = calcedGCost;
                openAtile->parent = currentAtile;
            }
           
        }
        return std::vector<Tile*>();
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