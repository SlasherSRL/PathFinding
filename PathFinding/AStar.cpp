#include "AStar.h"

AStar::AStar(Map& thismap): map(thismap)
{
    currentAtile = nullptr;
}
AStar::~AStar()
{
   
    
}
//float AStar::CalculateHCost(Tile* current, Tile* goal)
//{
//    int dx = std::abs(current->GetPosition().x - goal->GetPosition().x);
//    int dy = std::abs(current->GetPosition().y - goal->GetPosition().y);
//
//   
//    return std::sqrt(dx * dx + dy * dy);
//}
float AStar::GetDistance(std::shared_ptr<Tile> current, std::shared_ptr<Tile> destination) {
    int dstX = std::abs(current.get()->GetPosition().x - destination.get()->GetPosition().x);
    int dstY = std::abs(current.get()->GetPosition().y - destination.get()->GetPosition().y);

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

std::vector<std::shared_ptr<Tile>> AStar::FindPath(std::shared_ptr<Tile> start, std::shared_ptr<Tile> goal)
{
    if (finished)
    {
        return  std::vector<std::shared_ptr<Tile>>();
    }
   
    if (openListMap.empty())
    {
        //add start to here
    }

    if (!openListMap.empty())
    {
        std::shared_ptr<Atile> currentAtile = openListMap[0];



    }
   
    return std::vector<std::shared_ptr<Tile>>(); 
}

std::vector<std::shared_ptr<Tile>> AStar::RetracePath(std::shared_ptr<Atile> end)
{
    std::vector<std::shared_ptr<Tile>> path;
    std::shared_ptr<Atile> current = end;
    while (current != nullptr)
    {
        path.push_back(current->tile);
        
        current = current->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}