#include "Player.h"
#include <SDL\SDL.h>
#include <math.h>
Player::Player()
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
	std::_Vector_iterator<Human*> & humans,
	std::_Vector_iterator<Zombie*>& zombies)
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
	if (_inputManager->isKeyPressed(SDL_BUTTON_LEFT))
	{
		
		int gridwidth = 32;
		int gridHeight = 32;
		glm::vec2 mouseCoords = _inputManager->getMouseCoords();
		_position.x = floor(mouseCoords.x / gridwidth) * gridwidth;
		_position.y = floor(mouseCoords.y / gridHeight) * gridHeight;
			
		
		
	}
	
}