#pragma once
#include "Play.h"
enum TileType
{
	WALL,
	START,
	WALKABLE,
	GOAL,
	PATH
};
class Tile
{
private:
	TileType type;
	Play::Point2D position;
public:

	Tile(TileType tType, int x, int y,Play::Colour col);
	Play::Point2D GetPosition();
	TileType GetType();
	void SetType(TileType tip);

	Play::Colour color = Play::cBlack; 

	
	std::vector<std::shared_ptr<Tile>> neighbors;

};

struct Atile
{
	std::shared_ptr<Tile> tile;
	std::shared_ptr<Atile> parent;
	float gCost;
	float hCost;
	float fCost()const
	{
		return gCost + hCost;
	}
	bool operator<(const Atile& other)const
	{
		return fCost() < other.fCost();
	}
};

