#pragma once
#include <string>
#include <vector>
#include <Bengine\SpriteBatch.h>
#include <Bengine\ResourceManager.h>

const int TILE_WIDTH = 60;

class Level
{
public:
	Level(const std::string& fileName);
	~Level();

	void draw();
	const std::vector<std::string>& getLevelData() const{ return _levelData; }


	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }
	glm::vec2 getStartPlayerPos() const { return _startPlayerPosition; }
	const std::vector<glm::vec2>& getStartZombiePos() const { return _zombieStartPosition; }
	int getNumHumans() const { return _numHumans; }
private:

	std::vector<std::string> _levelData;
	int _numHumans;
	Bengine::SpriteBatch _spriteBatch;


	glm::vec2 _startPlayerPosition;
	std::vector<glm::vec2> _zombieStartPosition;
};

