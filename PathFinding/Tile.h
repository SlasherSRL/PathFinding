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
	float gCost;
	float hCost;
	float fCost()const;

	Tile* parent;


	std::vector<Tile> neighbors;

};

