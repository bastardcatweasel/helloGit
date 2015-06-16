#include "MainGame.h"

#include <Bengine/Bengine.h>
#include <Bengine\Timing.h>
#include <Bengine\Errors.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Zombie.h"
#include <random>
#include <ctime>

const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.30f;

MainGame::MainGame() : _screenWidth(500), _screenHeight(500), _gameState(GameState::PLAY), _fps(0), _player(nullptr)
{
    // Empty
}

MainGame::~MainGame() {
	for (int i = 0; i < _levels.size(); i++)
	{
		_levels[i] = nullptr;
		delete _levels[i];
	}
}

void MainGame::run() {
	initSystems();
	gameLoop();
}

void MainGame::initSystems() {
	// IMPLEMENT THIS!
	Bengine::init();
	_window.create("Awesome Screen", _screenWidth, _screenHeight, 0);
	glClearColor(0.6, 0.6, 0.6, 1);
	initShaders();
	_agentSpriteBatch.init();
	_camera.init(_screenWidth, _screenHeight);

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
	
	Bengine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60);
	
	while (_gameState == GameState::PLAY)
	{
		fpsLimiter.begin();
		processInput();

		updateAgents();
		_camera.setPosition(_player->getPosition());
		_camera.update();
		drawGame();
		
		_fps = fpsLimiter.end();

	}
}

void MainGame::updateAgents()
{
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
	}


	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(), _humans, _zombies);
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
void MainGame::processInput() {
    SDL_Event evnt;
    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                // Exit the game here!
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

	//draw player
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_agentSpriteBatch);
	}

	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_agentSpriteBatch);
	}

	_agentSpriteBatch.end();
	_agentSpriteBatch.renderBatch();
	_textureProgram.unuse();
    // Swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}
void MainGame::initLevel()
{
	_levels.push_back(new Level("levels/level1.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(4.0f, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager);


	std::mt19937 randomEngine(time(nullptr));
	
	 std::uniform_int_distribution<int> randX(1, _levels[_currentLevel]->getWidth() - 2);
	 std::uniform_int_distribution<int> randY(1, _levels[_currentLevel]->getHeight() -2 );

	
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


}