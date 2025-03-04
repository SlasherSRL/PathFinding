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
	for (Tile* tile : tiles) 
	{
		delete tile;  // Free each allocated tile
	}
	tiles.clear(); // Clear the vector to avoid dangling pointers 
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
			Tile* tile = nullptr;
			switch (mapData[row][col])
			{
			case 'X': type = WALL; 

				 tile = new Tile(type, col * tilesize, (height - 1 - row) * tilesize, Play::cBlack);
				
				tiles.push_back(tile); // make sure to flip Y
				break;
			case 'S': type = START; 
				 tile = new Tile(type, col * tilesize, (height - 1 - row) * tilesize, Play::cWhite);
				tiles.push_back(tile); 
				startTile = tile;// make sure to flip Y 
				break;
			case 'G': type = GOAL; 
				tile = new Tile(type, col * tilesize, (height - 1 - row) * tilesize, Play::cGreen); 
				tiles.push_back(tile); 
				goalTile = tile; // make sure to flip Y
				break;
			case '0': type = WALKABLE; 
				tile = new Tile(type, col * tilesize, (height - 1 - row) * tilesize, Play::cBlue);
				tiles.push_back(tile);
				 // make sure to flip Y
				break;
			}
			
		}
	}
}

void Map::Render(bool finished)
{
	for (Tile* tile : tiles)
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
void Map::RenderOneTile(Tile* tile)
{
	Play::DrawRect(
		{ tile->GetPosition().x - tilesize / 2 + offsetX, tile->GetPosition().y - tilesize / 2 + offsetY },
		{ tile->GetPosition().x + tilesize / 2 + offsetX, tile->GetPosition().y + tilesize / 2 + offsetY },
		tile->color, true);
}

void Map::DrawLines()
{
	for (Tile* tile : tiles)
	{
		for (Tile* neighbor : tile->neighbors)
		{
			
			Play::DrawLine({ tile->GetPosition().x + offsetX,tile->GetPosition().y + offsetY }, { neighbor->GetPosition().x+offsetX,neighbor->GetPosition().y + offsetY}, Play::cOrange);
			
			
		}
	}
}
//get tile based on position in vector
Tile* Map::GetTile(int x, int y)
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
			if (tiles[index]->GetType() == WALL)
			{
				continue; // Walls don't have neighbors
			}
				

			std::vector<Tile*> neighbors;
			

			for (const Direction& direc: directions)
			{
				int neighborsX = x + direc.x; // X index of neighbor
				int neighborsY = y + direc.y; // y index of neighbor

				// Ensure within bounds

				if (neighborsX >= 0 && neighborsX < width && neighborsY >= 0 && neighborsY < height)
				{
					int neighborIndex = neighborsY * stride + neighborsX;
					if (tiles[neighborIndex]->GetType() != WALL) // if not a wall
					{
						if (direc.x != 0 && direc.y != 0) // Is it a diagonal move?
						{
							// if its a diagonal make sure the ones next to it are not walls.
							if (tiles[(y)*stride + (x + direc.x)]->GetType() == WALL ||tiles[(y + direc.y) * stride + (x)]->GetType() == WALL)
							{
								//make it || if you dont want to be able to skip edges
								continue; 
							}

						}
						neighbors.push_back(tiles[neighborIndex]);
					}
				}
			}

			tiles[index]->neighbors = neighbors;
		}
	}
}
