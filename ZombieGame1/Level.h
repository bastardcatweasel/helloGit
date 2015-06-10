#pragma once
#include <string>
#include <vector>
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>

const int TILE_WIDTH = 8;

class Level
{
public:
	Level(const std::string& fileName);
	~Level();

	void draw();

private:

	std::vector<std::string> _levelData;
	int _numHumans;
	Bengine::SpriteBatch _spriteBatch;


	glm::ivec2 _startPlayerPosition;
	std::vector<glm::ivec2> _zombieStartPosition;
};

