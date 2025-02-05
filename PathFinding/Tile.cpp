#include "Tile.h"

Tile::Tile(TileType tType, int x, int y, Play::Colour col)
{
	type = tType;
	position.x = x;
	position.y = y;
	color = col;
}
void Tile::SetType(TileType tip)
{
	type = tip;
}

Play::Point2D Tile::GetPosition()
{
	return position;
}
TileType Tile::GetType()
{
	return type;
}


