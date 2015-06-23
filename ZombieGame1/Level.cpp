#include "Level.h"
#include <fstream>
#include <Bengine\BengineErrors.h>
#include <iostream>
#include <Bengine\ResourceManager.h>

Level::Level(const std::string& fileName)
{
	

	std::ifstream file;
	file.open(fileName);

	if (file.fail())
	{
		Bengine::fatalError("failed to open File" + fileName);
	}

	std::string tmp;

	file >> tmp >> _numHumans;

	std::getline(file, tmp);

	while (std::getline(file, tmp))
	{
		_levelData.push_back(tmp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();


	glm::vec4 uvRect(0, 0, 1, 1);
	Bengine::ColorRGBA8 whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	for (int y = 0; y < _levelData.size(); y++)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			
			//get Tile
			char tile = _levelData[y][x];
			//get dest rwect
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			switch (tile)
			{
			case 'R':
			case 'B':
				_spriteBatch.draw(destRect, uvRect, Bengine::ResourceManager::getTexture("Textures/red_bricks.png").id, 0.0f, whiteColor);
				break;

			case 'G':
				_spriteBatch.draw(destRect, uvRect, Bengine::ResourceManager::getTexture("Textures/glass.png").id, 0.0f, whiteColor);
				break;

			case 'L':
				_spriteBatch.draw(destRect, uvRect, Bengine::ResourceManager::getTexture("Textures/light_bricks.png").id, 0.0f, whiteColor);
				break;

			case '@':
				    _levelData[y][x] = '.';
					_startPlayerPosition.x = x * TILE_WIDTH;
					_startPlayerPosition.y = y * TILE_WIDTH;
					break;

			case 'Z':
				_levelData[y][x] = '.';
				_zombieStartPosition.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
					break;


			case '.':
				break;
			default:
				std::printf("fucked up");
				
			}
		}
	}

	_spriteBatch.end();
}


Level::~Level()
{
}

void Level::draw()
{
	_spriteBatch.renderBatch();
}