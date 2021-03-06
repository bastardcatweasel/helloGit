#include "MainGame.h"

#include <Bengine/Bengine.h>
#include <Bengine\Timing.h>
#include <SDL/SDL.h>
#include <iostream>


MainGame::MainGame() : _screenWidth(500), _screenHeight(500), _gameState(GameState::PLAY), _fps(0)
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

	_camera.init(_screenWidth, _screenHeight);
	_levels.push_back(new Level("levels/level1.txt"));
	_currentLevel = 0;



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
		_camera.update();
		drawGame();
		
		_fps = fpsLimiter.end();

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
	glm::mat4 projectionMatrix = _camera.getCameraMatrix();

	GLint pUniform = _textureProgram.getUniformLocation("P");

	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	_levels[_currentLevel]->draw();


	_textureProgram.unuse();
    // Swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}