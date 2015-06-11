#pragma once
#include <string>
#include <vector>
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>

const int TILE_WIDTH = 32;

class Level
{
public:
	Level(const std::string& fileName);
	~Level();

	void draw();

	glm::vec2 getStartPlayerPos() const { return _startPlayerPosition; }
	const std::vector<glm::vec2>& getStartZombiePos() const { return _zombieStartPosition; }
private:

	std::vector<std::string> _levelData;
	int _numHumans;
	Bengine::SpriteBatch _spriteBatch;


	glm::vec2 _startPlayerPosition;
	std::vector<glm::vec2> _zombieStartPosition;
};

