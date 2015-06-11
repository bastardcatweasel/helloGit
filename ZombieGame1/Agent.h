#pragma once

#include <glm\glm.hpp>
#include <Bengine/SpriteBatch.h>

const int AGENT_WIDTH = 60;
class Agent
{
public:
	Agent();
	virtual ~Agent();

	virtual void update() = 0;
	void draw(Bengine::SpriteBatch& spriteBatch);
protected:
	glm::vec2 _position;
	float _speed;
	Bengine::Color _color;

};

