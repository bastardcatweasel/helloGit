#include "MainGame.h"

#include <Bengine/Bengine.h>
#include <Bengine\Timing.h>
#include <Bengine\BengineErrors.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Zombie.h"
#include <random>
#include <ctime>
#include <algorithm>
#include "Gun.h"
#include <Bengine/AudioEngine.h>
#include <Bengine\ResourceManager.h>
#include <glm\gtx\rotate_vector.hpp>

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.30f;

MainGame::MainGame() : _screenWidth(500), _screenHeight(500), _gameState(GameState::PLAY), _fps(0), _player(nullptr), _numHumansKilled(0), _numZombiesKilled(0)
{
    // Empty
}

MainGame::~MainGame() {
	for (auto i = 0; i < _levels.size(); i++)
	{
		_levels[i] = nullptr;
		delete _levels[i];
	}
	for (auto i = 0; i < _humans.size(); i++)
	{
		_humans[i] = nullptr;
		delete _humans[i];
	}

	for (auto i = 0; i < _zombies.size(); i++)
	{
		_zombies[i] = nullptr;
		delete _zombies[i];
	}
}

void MainGame::run() {
	initSystems();

	Bengine::Music music = m_audioEngine.loadMusic("Sound/XYZ.ogg");
	music.play(-1);
	gameLoop();
}

void updateBloodParticle(Bengine::Particle2D& particle, float deltaTime)
{
	particle.position += particle.velocity * deltaTime;
	particle.color.a = (GLubyte)(particle.life * 255.0f);
}

void MainGame::initSystems() {
	// IMPLEMENT THIS!
	Bengine::init();
	m_audioEngine.init();
	_window.create("Awesome Screen", _screenWidth, _screenHeight, 0);
	glClearColor(0.6, 0.6, 0.6, 1);
	initShaders();
	_hudSpriteBatch.init();
	_agentSpriteBatch.init();

	_spriteFont = new Bengine::SpriteFont("Fonts/leadcoat.ttf", 32);
	_camera.init(_screenWidth, _screenHeight);
	_hudCamera.init(_screenWidth, _screenHeight);
	_hudCamera.setPosition(glm::vec2(_screenWidth / 2, _screenHeight / 2));
	//init Particles
	m_bloodParticleBatch = new Bengine::ParticleBatch2D;
	m_bloodParticleBatch->init(1000, 0.05f, Bengine::ResourceManager::getTexture("Textures/particle.png"), [](Bengine::Particle2D& particle, float deltaTime) {
		particle.position += particle.velocity * deltaTime;
		particle.color.a = (GLubyte)(particle.life * 255.0f);
	});
	m_particleEngine.addParticleBatch(m_bloodParticleBatch);
	initLevel();
	


}

void MainGame::initShaders() {
    // Compile our color shader
    _textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    _textureProgram.addAttribute("vertexPosition");
    _textureProgram.addAttribute("vertexColor");
    _textureProgram.addAttribute("vertexUV");
    _textureProgram.linkShaders();
}

void MainGame::gameLoop() {
	const float DESIRED_FPS = 60.0f;
	const int MAX_PHYSICS_STEPS = 6;
	Bengine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(600000.0f);
	
	const float CAMERA_SCALE = 1.0f / 3.0f;
	_camera.setScale(CAMERA_SCALE);

	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAMETIME= MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f;
	float previousTicks = SDL_GetTicks();

	while (_gameState == GameState::PLAY)
	{
		
		fpsLimiter.begin();
		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		float totalDeltaTime = frameTime / DESIRED_FRAMETIME;
		checkVictory();

		_inputManager.update();
		processInput();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
		{
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			updateAgents(deltaTime);
			updateBullets(deltaTime);
			m_particleEngine.update(deltaTime);
			totalDeltaTime -= deltaTime;
			i++;
		}

		
		_camera.setPosition(_player->getPosition());
		_camera.update();
		
		
		_hudCamera.update();


		drawGame();
		
		_fps = fpsLimiter.end();

		std::cout << _fps << std::endl;
	}
}

void MainGame::updateAgents(float deltaTime)
{
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies,deltaTime);
	}


	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies, deltaTime);
	}

	//Update Z collision
	for (int i = 0; i < _zombies.size(); i++)
	{
		for (int j = i + 1; j < _zombies.size(); j++)
		{
			_zombies[i]->collideWithAgent(_zombies[j]);
		}
	}

	//coolide with h
	for (int i = 0; i < _zombies.size(); i++)
	{
		for (int j = 1; j < _humans.size(); j++)
		{

			if (_zombies[i]->collideWithAgent(_humans[j]))
			{
				//add zom
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED,_humans[j]->getPosition());

				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}


		if (_zombies[i]->collideWithAgent(_player))
		{
			Bengine::fatalError("YOU LOSE");
		}
	}

	//update Human Collision
	for (int i = 0; i < _humans.size(); i++)
	{
		for (int j = i + 1; j < _humans.size(); j++)
		{
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}

	

}

void MainGame::checkVictory()
{
	if (_zombies.empty())
	{
		std::printf("*****You win!!!!*****\n You Killed %d humans and %d zombies. There are %d/%d humans Remaining\n", _numHumansKilled,_numZombiesKilled, _humans.size()-1, _levels[_currentLevel]->getNumHumans());
		Bengine::fatalError("");
	}


}
void MainGame::processInput() {
    SDL_Event evnt;
    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
				_gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.releaseKey(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.pressKey(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManager.releaseKey(evnt.button.button);
                break;
        }
    }
}

void MainGame::drawGame() {
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);


	glm::mat4 projectionMatrix = _camera.getCameraMatrix();

	GLint pUniform = _textureProgram.getUniformLocation("P");

	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	//draw level
	_levels[_currentLevel]->draw();
	_agentSpriteBatch.begin();
	
	
	const glm::vec2 agentDims(AGENT_RADIUS * 2.0f);
	//draw player
	for (int i = 0; i < _humans.size(); i++)
	{
		if (_camera.isBoxinView(_humans[i]->getPosition(), agentDims))
		{
			_humans[i]->draw(_agentSpriteBatch);
		}

	}

	for (int i = 0; i < _zombies.size(); i++)
	{

		if (_camera.isBoxinView(_zombies[i]->getPosition(), agentDims))
		{
			_zombies[i]->draw(_agentSpriteBatch);
		}
	}

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].draw(_agentSpriteBatch);
	}
	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();

	m_particleEngine.draw(&_agentSpriteBatch);

	drawHud();

	_textureProgram.unuse();
    // Swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}
void MainGame::initLevel()
{
	_levels.push_back(new Level("levels/level1.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(4.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullets);


	std::mt19937 randomEngine(time(nullptr));
	
	 std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
	 std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() -2 );

	
	std::cout << _levels[_currentLevel]->getNumHumans();
	_humans.push_back(_player);



	for (int i = 0; i < _levels[_currentLevel]->getNumHumans(); i++)
	{
		_humans.push_back(new Human);
		glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED,pos);

	}
	

	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getStartZombiePos();
	for (int i = 0; i < zombiePositions.size(); i++)
	{
		_zombies.push_back(new Zombie);
		
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	//set up guns
	_player->addGun(new Gun("Magnum", 20, 1, 0, 30, 20, m_audioEngine.loadSoundEffect("Sound/shots/pistol.wav")));
	_player->addGun(new Gun("ShotGun", 40, 10, .5, 20, 20, m_audioEngine.loadSoundEffect("Sound/shots/shotgun.wav")));
	_player->addGun(new Gun("MP5", 1, 3, 0.02, 20, 20, m_audioEngine.loadSoundEffect("Sound/shots/rifle.wav")));
}

void MainGame::drawHud()
{
	char buffer[256];


	glm::mat4 projectionMatrix = _hudCamera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);


	_hudSpriteBatch.begin();

	sprintf_s(buffer, "Num Humans %d", _humans.size());
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(0,0),
					  glm::vec2(0.5), 0.0f, Bengine::ColorRGBA8(255, 255, 255, 255));
	
	
	sprintf_s(buffer, "Num Zombies %d", _zombies.size());
	_spriteFont->draw(_hudSpriteBatch, buffer, glm::vec2(0, 36),
		glm::vec2(0.5), 0.0f, Bengine::ColorRGBA8(255, 255, 255, 255));


	_hudSpriteBatch.end();
	_hudSpriteBatch.renderBatch();
}
void MainGame::updateBullets(float deltaTime)
{
	for (int i = 0; i < _bullets.size();)
	{
		if (_bullets[i].update(_levels[_currentLevel]->getLevelData(),deltaTime))
		{
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
		{
			i++;
		}

	}

	bool wasBulletRemoved;

	for (int i = 0; i < _bullets.size();i++)
	{
		wasBulletRemoved = false;
		for (int j = 0; j < _zombies.size();)
		{
			if (_bullets[i].collideWithAgent(_zombies[j]))
			{
				addBlood(_bullets[i].getPosition(), 5);


				if (_zombies[j]->applyDamage(_bullets[i].getDamage()))
				{
					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
					_numZombiesKilled++;

				}
				else{
					j++;
				}
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				wasBulletRemoved = true;
				break;
			
			}
			else{
				j++;
			}



		}
		if (wasBulletRemoved == false)
		{
			for (int j = 1; j < _humans.size();)
			{
				if (_bullets[i].collideWithAgent(_humans[j]))
				{

					addBlood(_bullets[i].getPosition(), 5);

					if (_humans[j]->applyDamage(_bullets[i].getDamage()))
					{
						delete _humans[j];
						_humans[j] = _humans.back();
						_humans.pop_back();
						_numHumansKilled++;

					}
					else{
						j++;
					}
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					wasBulletRemoved = true;
					break;

				}
				else{
					j++;
				}



			}
		}
	}

	

}

void MainGame::addBlood(glm::vec2& position, int numParticles)
{
	static std::mt19937 randEngine(time(nullptr));
	static std::uniform_real_distribution<float> randAngle(0.0f, 360.f);
	glm::vec2 vel(1.0f, 0.0f);
	Bengine::ColorRGBA8 color(255, 0, 0, 255);
	glm::rotate(vel, randAngle(randEngine));

	for (int i = 0; i < numParticles; i++)
	{
		m_bloodParticleBatch->addParticle(position, glm::rotate(vel, randAngle(randEngine)), color, 30.0f);
	}
}