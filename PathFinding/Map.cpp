#include "Map.h"

Map::Map(const char* filePath)
{
	startTile = nullptr;
	goalTile = nullptr;
	LoadFromFile(filePath);
	
	SetupNeighbors();
}
Map::~Map()
{

}
void Map::SetOffset(int offsetXs, int offsetYs)
{
	offsetX = offsetXs;
	offsetY = offsetYs;


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
	tiles.reserve(width * height);
	stride = width;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			TileType type;
			switch (mapData[row][col])
			{
			case 'X': type = WALL; 


				tiles.emplace_back(std::make_shared<Tile>(type, col * tilesize, (height - 1 - row) * tilesize,Play::cBlack)); // make sure to flip Y
				break;
			case 'S': type = START; 
				startTile = tiles.emplace_back(std::make_shared<Tile>(type, col * tilesize, (height - 1 - row) * tilesize, Play::cWhite)); // make sure to flip Y 
				break;
			case 'G': type = GOAL; 
				goalTile = tiles.emplace_back(std::make_shared<Tile>(type, col * tilesize, (height - 1 - row) * tilesize, Play::cGreen)); // make sure to flip Y
				break;
			case '0': type = WALKABLE; 
				tiles.emplace_back(std::make_shared<Tile>(type, col * tilesize, (height - 1 - row) * tilesize, Play::cBlue)); // make sure to flip Y
				break;
			}
			
		}
	}
}

void Map::Render(bool finished)
{
	for (std::shared_ptr<Tile> tile : tiles)
	{
		if (finished)
		{
			
			switch (tile->GetType())
			{

			case WALL:      tile->color = Play::cBlack; break;
			case START:     tile->color = Play::cWhite; break;
			case WALKABLE:  tile->color = Play::cBlue;  break;
			case GOAL:      tile->color = Play::cGreen;   break;
			case PATH: tile->color = Play::cGreen; break;
			}
		}
		Play::DrawRect(
			{ tile->GetPosition().x -tilesize / 2+offsetX, tile->GetPosition().y - tilesize / 2+offsetY},
			{ tile->GetPosition().x + tilesize / 2+offsetX, tile->GetPosition().y + tilesize / 2+offsetY},
			tile->color, true);
		
	}

}
void Map::RenderOneTile(std::shared_ptr<Tile> tile)
{
	Play::DrawRect(
		{ tile.get()->GetPosition().x - tilesize / 2 + offsetX, tile.get()->GetPosition().y - tilesize / 2 + offsetY },
		{ tile.get()->GetPosition().x + tilesize / 2 + offsetX, tile.get()->GetPosition().y + tilesize / 2 + offsetY },
		tile.get()->color, true);
}

void Map::DrawLines()
{
	for (std::shared_ptr<Tile> tile : tiles)
	{
		for (std::weak_ptr<Tile> wekneighbor : tile->neighbors)
		{
			if(auto neighbor= wekNeighbor.lock())
			{
				Play::DrawLine({ tile->GetPosition().x + offsetX,tile->GetPosition().y + offsetY }, { neighbor->GetPosition().x+offsetX,neighbor->GetPosition().y + offsetY}, Play::cOrange);
			}
			
		}
	}
}
//get tile based on position in vector
std::shared_ptr<Tile> Map::GetTile(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return nullptr; // Out of bounds

	return tiles[y * stride + x];
}

void Map::SetupNeighbors()
{
	std::vector<Direction> directions =
	{
		Direction(-1,  0), // Left
		Direction(1,  0),  // Right
		Direction(0, -1),  // Up
		Direction(0,  1),  // Down
		Direction(-1, -1), // Top-left (diagonal)
		Direction(-1,  1), // Bottom-left (diagonal)
		Direction(1, -1),  // Top-right (diagonal)
		Direction(1,  1)   // Bottom-right (diagonal)
	};
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int index = y * stride + x; // X is in this direct - - - - - >, stride jumps a complete line, y says how many lines to jump
			if (tiles[index].get()->GetType() == WALL)
			{
				continue; // Walls don't have neighbors
			}
				

			std::vector<std::weak_ptr<Tile>> neighbors;
			

			for (const Direction& direc: directions)
			{
				int neighborsX = x + direc.x; // X index of neighbor
				int neighborsY = y + direc.y; // y index of neighbor

				// Ensure within bounds

				if (neighborsX >= 0 && neighborsX < width && neighborsY >= 0 && neighborsY < height)
				{
					int neighborIndex = neighborsY * stride + neighborsX;
					if (tiles[neighborIndex].get()->GetType() != WALL) // if not a wall
					{
						if (direc.x != 0 && direc.y != 0) // Is it a diagonal move?
						{
							// if its a diagonal make sure the ones next to it are not walls.
							if (tiles[(y)*stride + (x + direc.x)].get()->GetType() == WALL &&tiles[(y + direc.y) * stride + (x)].get()->GetType() == WALL)
							{
								//make it || if you dont want to be able to skip edges
								continue; 
							}

						}
						neighbors.push_back(tiles[neighborIndex]);
					}
				}
			}

			tiles[index].get()->neighbors = neighbors;
		}
	}
}
