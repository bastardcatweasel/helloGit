#include "Player.h"
#include <SDL\SDL.h>
#include <math.h>
Player::Player() : _currentGunIndex(-1)
{
}


Player::~Player()
{
}
void Player::init(float speed, glm::vec2 position, Bengine::InputManager* inputManager)
{
	_speed = speed;
	_position = position;
	_inputManager = inputManager;
	_color.r = 0;
	_color.g = 0;
	_color.b = 220;
	_color.a = 255;
}
void Player::update(const std::vector<std::string> &levelData,
	std::vector<Human*>&  humans,
	std::vector<Zombie*>& zombies)
{
	if (_inputManager->isKeyPressed(SDLK_w))
	{
		_position.y += _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_s)){
		_position.y -= _speed;
	}

	if (_inputManager->isKeyPressed(SDLK_a))
	{
		_position.x -= _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_d)){
		_position.x += _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_1) && _guns.size() >= 0)
	{
		
		_currentGunIndex = 0;
				
	}
	else if (_inputManager->isKeyPressed(SDLK_2) && _guns.size() >= 0)
	{

		_currentGunIndex = 1;

	}


	collideWithLevel(levelData);
	
}

void Player::addGun(Gun * gun)
{
	_guns.push_back(gun);

	if (_currentGunIndex == -1) _currentGunIndex = 0;
}