#pragma once
#include "Human.h"
#include <Bengine/InputManager.h>
#include <Bengine\Camera2D.h>

class Player : public Human
{
public:
	Player();
	~Player();
	void init(float speed, glm::vec2 position, Bengine::InputManager* inputManager);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*> &humans,
		std::vector<Zombie*> & zombies);
private:
	Bengine::InputManager* _inputManager;
};

