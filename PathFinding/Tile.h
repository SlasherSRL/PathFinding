#pragma once
#include "Play.h"
enum TileType
{
	WALL,
	START,
	WALKABLE,
	GOAL
};
class Tile
{
private:
	TileType type;
	Play::Point2D position;
public:

	Tile(TileType tType, int x, int y);
	Play::Point2D GetPosition();
	TileType GetType();
	//A* stuff
	Play::Colour color= Play::cBlack;

	
	std::vector<Tile*> neighbors;

};

struct Atile
{
	Tile* tile;
	Tile* parent;
	float gCost;
	float hCost;
	float fCost()const
	{
		return gCost + hCost;
	}
};
