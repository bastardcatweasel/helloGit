#include "Gun.h"
#include <random>
#include <ctime>
#include <glm\gtx\rotate_vector.hpp>
Gun::Gun(std::string name, int fireRate, int bulltsPerShot, float spread, float bulletSpeed, float bulletDamage, Bengine::SoundEffect fireEffect) :
_name(name), 
_fireRate(fireRate), 
_bulletsPerShot(bulltsPerShot), 
_spread(spread), 
_bulletSpeed(bulletSpeed), 
_bulletDamage(bulletDamage),
_frameCounter(0),
m_fireEffect(fireEffect)
{


}


Gun::~Gun()
{
}
void Gun::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime)
{
	_frameCounter += 1.0f * deltaTime;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		fire(direction, position, bullets);
		_frameCounter = 0;

	}
}


void Gun::fire(glm::vec2 direction, const glm::vec2& position, std::vector<Bullet>& bullets)
{

	std::mt19937 randomEngine(time(nullptr));

	std::uniform_real_distribution<float> randRotate(-_spread , _spread );


	m_fireEffect.play();
	for (int i = 0; i < _bulletsPerShot; i++)
	{


		bullets.emplace_back(position, glm::rotate(direction, randRotate(randomEngine)), _bulletDamage, _bulletSpeed);
	}
}