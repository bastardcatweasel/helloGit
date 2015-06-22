#pragma once
#include <string>
#include "Bullet.h"
#include <glm\glm.hpp>
#include <vector>
class Gun
{
public:
	Gun(std::string name,int fireRate, int bulltsPerShot, float spread, float bulletSpeed, float bulletDamage);
	~Gun();
	
	void update(bool isMouseDown,const glm::vec2& position, const glm::vec2& direction, std::vector<Bullet>& bullets, float deltaTime);
private:
	std::string _name;
	void fire(glm::vec2 direction, const glm::vec2& position, std::vector<Bullet>& bullets);
	int _fireRate; //in terms of frames
	
	float _spread; // accuracy
	
	int _bulletsPerShot;

	float _bulletSpeed;
	float _bulletDamage;

	float _frameCounter;
};

