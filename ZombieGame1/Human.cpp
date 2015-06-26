#include "Human.h"
#include <random>
#include <ctime>
#include <Bengine\ResourceManager.h>
#include <glm\gtx\rotate_vector.hpp>
Human::Human() : _frames(0)
{
}


Human::~Human()
{
}
void Human::update(const std::vector<std::string> &levelData,
	std::vector<Human*> &humans,
	std::vector<Zombie*> & zombies,
	float deltaTime)
{

	

	std::mt19937 randomEngine(time(nullptr));

	std::uniform_real_distribution<float> randRotate(-0.0f, 0.50f);
	_position += m_direction * _speed * deltaTime;


	if (_frames == 20)
	{
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
		_frames = 0;
	}
	else
	{
		_frames++;
	}

	if (collideWithLevel(levelData))
	{
		m_direction = glm::rotate(m_direction, randRotate(randomEngine));
	}

	

}
void Human::init(float speed, glm::vec2 pos)
{
	static std::mt19937 randomEngine(time(nullptr));

	
	
	static std::uniform_real_distribution<float> randDir(0.0f, 0.5f);
	
	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;
	_health = 20;
	_speed = speed;
	_position = pos;
	m_direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	m_textureID = Bengine::ResourceManager::getTexture("Textures/human.png").id;

	if (m_direction.length() == 0)m_direction = glm::vec2(1.0f, 0.0f);
	
	m_direction = glm::normalize(m_direction);

}