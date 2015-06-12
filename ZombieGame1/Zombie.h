#pragma once
#include "Agent.h"
class Zombie : public Agent
{
public:
	Zombie();
	~Zombie();


	virtual void update(const std::vector<std::string> &levelData,
		std::_Vector_iterator<Human*> & humans,
		std::_Vector_iterator<Zombie*>& zombies);
};

