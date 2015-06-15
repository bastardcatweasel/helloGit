#pragma once
#include "Agent.h"

class Human : public Agent
{
public:
	Human();
	 virtual ~Human();
	 virtual void update(const std::vector<std::string> &levelData,
		 std::vector<Human*> &humans,
		 std::vector<Zombie*> & zombies);
	 void init(float speed, glm::vec2 pos);
private:


	glm::vec2 _direction;

	int _frames;

};

