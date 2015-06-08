#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <Bengine/Sprite.h>
#include <Bengine/Errors.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/GLTexture.h>
#include <vector>
#include <Bengine/Window.h>
#include <Bengine\Bengine.h>
#include <Bengine\Window.h>
#include <Bengine/Camera2D.h>
#include <Bengine\SpriteBatch.h>
#include <Bengine/ResourceManager.h>
#include <Bengine\InputManager.h>
#include <Bengine/Timing.h>
#include "Bullet.h"


enum class GameState{ PLAY, EXIT };

	class MainGame
	{
	public:
		MainGame();
		~MainGame();
		void run();


	private:
		Bengine::Window _window;
		int _screenWidth;
		int _screenHeight;

		void initShaders();
		void initSystems();
		void processInput();
		void gameLoop();
		void drawGame();
		GameState _gameState;
		
		Bengine::SpriteBatch _spriteBatch;
		Bengine::InputManager _inputManager;
		Bengine::FpsLimiter _fpsLimiter;
		
		Bengine::Sprite _sprite;
		
		float _maxFPS;
		Bengine::GLTexture _playerTexture;
		float _time;
		float _fps;
		
		std::vector<Bullet> _bullets;
		
		Bengine::GLSLProgram _colorProgram;
		Bengine::Camera2D _camera;
	};

