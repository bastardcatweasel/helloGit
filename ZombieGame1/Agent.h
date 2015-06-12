#pragma once

#include <glm\glm.hpp>
#include <Bengine/SpriteBatch.h>

const int AGENT_WIDTH = 60;
class Zombie;
class Human;


class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update(const std::vector<std::string> &levelData,
		std::_Vector_iterator<Human*> & humans,
		std::_Vector_iterator<Zombie*>& zombies) = 0;
	void draw(Bengine::SpriteBatch& spriteBatch);


	void collideWithLevel(const std::vector<std::string>& levelData);
	glm::vec2 getPosition() const { return _position; }
protected:
	glm::vec2 _position;
	float _speed;
	Bengine::Color _color;

};

