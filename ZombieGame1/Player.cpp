#include "Player.h"
#include <SDL\SDL.h>
#include <math.h>
#include "Bullet.h"
#include "Gun.h"
#include <Bengine\ResourceManager.h>
Player::Player() : _currentGunIndex(-1)
{
}


Player::~Player()
{
}
void Player::init(float speed, glm::vec2 position, Bengine::InputManager* inputManager, Bengine::Camera2D* camera, std::vector<Bullet>* bullets)
{
	_speed = speed;
	_position = position;
	_inputManager = inputManager;
	_camera = camera;
	_bullets = bullets;
	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;
	m_textureID = Bengine::ResourceManager::getTexture("Textures/player.png").id;
}
void Player::update(const std::vector<std::string> &levelData,
	std::vector<Human*>&  humans,
	std::vector<Zombie*>& zombies,
	float deltaTime)
{
	if (_inputManager->isKeyDown(SDLK_w))
	{
		_position.y += _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_s)){
		_position.y -= _speed * deltaTime;
	}

	if (_inputManager->isKeyDown(SDLK_a))
	{
		_position.x -= _speed * deltaTime;
	}
	else if (_inputManager->isKeyDown(SDLK_d)){
		_position.x += _speed * deltaTime;
	}
	if (_inputManager->isKeyDown(SDLK_1) && _guns.size() >= 0)
	{
		
		_currentGunIndex = 0;
				
	}
	else if (_inputManager->isKeyDown(SDLK_2) && _guns.size() >= 1)
	{

		_currentGunIndex = 1;

	}
	else if (_inputManager->isKeyDown(SDLK_3) && _guns.size() >= 2)
	{

		_currentGunIndex = 2;

	}
	if (_currentGunIndex != -1)
	{
		glm::vec2 mouseCoords = _inputManager->getMouseCoords();
		mouseCoords = _camera->convertScreenToWorld(mouseCoords);
		glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
		glm::vec2 direction = glm::normalize(mouseCoords - centerPosition);

		_guns[_currentGunIndex]->update(_inputManager->isKeyPressed(SDL_BUTTON_LEFT), centerPosition, direction, *_bullets, deltaTime);
	}

	collideWithLevel(levelData);
	
}

void Player::addGun(Gun * gun)
{
	_guns.push_back(gun);

	if (_currentGunIndex == -1) _currentGunIndex = 0;
}