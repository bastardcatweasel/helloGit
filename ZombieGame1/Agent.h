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
		std::vector<Zombie*> & zombies, float deltaTime) = 0;
	void draw(Bengine::SpriteBatch& spriteBatch);
	bool collideWithLevel(const std::vector<std::string>& levelData);
	bool collideWithAgent(Agent* agent);
	bool applyDamage(float damage);
	glm::vec2 getPosition() const { return _position; }
protected:
	glm::vec2 _position;
	float _speed;
	float _health;
	Bengine::ColorRGBA8 _color;
	void checkTilePosition(std::vector<glm::vec2>& collideTilePosition,
		const std::vector<std::string>& levelData,
		float x, float y);

	void collideWithTile(glm::vec2 tilePos);

	GLuint m_textureID;
	glm::vec2 m_direction = glm::vec2(1.0, 0.0);
	
};

