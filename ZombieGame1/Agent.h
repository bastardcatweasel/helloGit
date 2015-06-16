#pragma once

#include <glm\glm.hpp>
#include <Bengine/SpriteBatch.h>

const int AGENT_WIDTH = 60;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;
class Zombie;
class Human;


class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update(const std::vector<std::string> &levelData,
		std::vector<Human*> &humans,
		std::vector<Zombie*> & zombies) = 0;
	void draw(Bengine::SpriteBatch& spriteBatch);
	bool collideWithLevel(const std::vector<std::string>& levelData);
	bool collideWithAgent(Agent* agent);
	
	glm::vec2 getPosition() const { return _position; }
protected:
	glm::vec2 _position;
	float _speed;
	Bengine::Color _color;
	void checkTilePosition(std::vector<glm::vec2>& collideTilePosition,
		const std::vector<std::string>& levelData,
		float x, float y);

	void collideWithTile(glm::vec2 tilePos);


	
};

