#include "Human.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>
Human::Human() : _frames(0)
{
}


Human::~Human()
{
}
void Human::update(const std::vector<std::string> &levelData,
	std::vector<Human*> &humans,
	std::vector<Zombie*> & zombies)
{

	

	std::mt19937 randomEngine(time(nullptr));

	std::uniform_real_distribution<float> randRotate(-0.0f, 0.50f);
	_position += _direction * _speed;


	if (_frames == 20)
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
		_frames = 0;
	}
	else
	{
		_frames++;
	}

	if (collideWithLevel(levelData))
	{
		_direction = glm::rotate(_direction, randRotate(randomEngine));
	}

	

}
void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine(time(nullptr));

	
	
	static std::uniform_real_distribution<float> randDir(0.0f, 0.5f);
	
	_color.r = 200;
	_color.g = 0;
	_color.b = 200;
	_color.a = 255;
	_health = 20;
	_speed = speed;
	_position = pos;
	_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));

	if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);
	
	_direction = glm::normalize(_direction);

}