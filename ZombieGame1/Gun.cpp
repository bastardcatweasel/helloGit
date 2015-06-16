#include "Gun.h"


Gun::Gun(std::string name, int fireRate, int bulltsPerShot, float spread, float bulletSpeed, float bulletDamage) :
_name(name), 
_fireRate(fireRate), 
_bulletsPerShot(bulltsPerShot), 
_spread(spread), 
_bulletSpeed(bulletSpeed), 
_bulletDamage(bulletDamage),
_frameCounter(0)
{


}


Gun::~Gun()
{
}
void Gun::update(bool isMouseDown, const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets)
{
	_frameCounter++;
	if (_frameCounter >= _fireRate && isMouseDown)
	{
		fire(direction, position, bullets);
		_frameCounter = 0;

	}
}


void Gun::fire(glm::vec2 direction, const glm::vec2& position, std::vector<Bullet>& bullets)
{
	for (int i = 0; i < _bulletsPerShot; i++)
	{
		bullets.emplace_back(position, direction, _bulletDamage, _bulletSpeed);
	}
}