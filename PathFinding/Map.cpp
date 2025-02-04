#include "Map.h"

Map::Map(const char* filePath)
{
	LoadFromFile(filePath);
}

void Map::LoadFromFile(const char* filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return;
	}
	std::vector<std::string> mapData;
	std::string line;

	while (std::getline(file, line))
	{
		mapData.push_back(line);
	}
	file.close();

	tiles.clear();//make sure tiles is empty
	width = mapData[0].size();
	height = mapData.size();
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			TileType type;
			switch (mapData[row][col])
			{
			case 'X': type = WALL; break;
			case 'S': type = START; break;
			case 'G': type = GOAL; break;
			case '0': type = WALKABLE; break;
			}
			tiles.emplace_back(type, col * tilesize, (height-1-row) *tilesize); // make sure to flip Y
		}
	}
}

void Map::Render()
{
	for (Tile tile : tiles)
	{
		Play::Colour color = Play::cBlack;

		switch (tile.GetType())
		{
		case WALL:
			color = Play::cBlack;
			break;
		case WALKABLE:
			color = Play::cBlue;
			break;
		case GOAL:
			color = Play::cGreen;
			break;
		case START:
			color = Play::cYellow;
			break;
		}
		Play::DrawRect(
			{ tile.GetPosition().x -tilesize / 2, tile.GetPosition().y - tilesize / 2},  
			{ tile.GetPosition().x + tilesize / 2, tile.GetPosition().y + tilesize / 2},  
			color, true);

	}
}

Tile* Map::GetTile(int x, int y)
{
	return nullptr;
}
void Map::SetupNeighbors()
{

}