#pragma once
#include "Human.h"
#include <Bengine/InputManager.h>
#include <Bengine\Camera2D.h>



class Gun;
class Bullet;
class Player : public Human
{
public:
	Player();
	~Player();
	void init(float speed, glm::vec2 position, Bengine::InputManager* inputManager, Bengine::Camera2D* camera, std::vector<Bullet>* bullets);
	void update(const std::vector<std::string>& levelData,
		std::vector<Human*> &humans,
		std::vector<Zombie*> & zombies);

	void addGun(Gun * gun);

private:
	Bengine::InputManager* _inputManager;
	Bengine::Camera2D* _camera;
	std::vector<Gun*> _guns;
	int _currentGunIndex;
	std::vector<Bullet>* _bullets;
};

