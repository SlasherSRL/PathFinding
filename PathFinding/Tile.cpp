#include "Tile.h"

Tile::Tile(TileType tType, int x, int y)
{
	type = tType;
	position.x = x;
	position.y = y;

	gCost = 0;
	hCost = 0;
	parent = nullptr;
}
Play::Point2D Tile::GetPosition()
{
	return position;
}
TileType Tile::GetType()
{
	return type;
}
