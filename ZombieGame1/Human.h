#pragma once
#include "Agent.h"

class Human : public Agent
{
public:
	Human();
	 virtual ~Human();
	 virtual void update(const std::vector<std::string> &levelData,
		 std::_Vector_iterator<Human*> & humans,
		 std::_Vector_iterator<Zombie*>& zombies);
};

