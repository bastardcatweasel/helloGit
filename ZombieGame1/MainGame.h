#pragma once

#include <Bengine/Window.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/Camera2D.h>
#include <Bengine/InputManager.h>
#include <Bengine\SpriteFont.h>
#include "Level.h"
#include "Player.h"
#include <vector>
#include <Bengine\SpriteBatch.h>
#include "Bullet.h"
#include <Bengine/AudioEngine.h>
#include <Bengine\ParticleEngine2D.h>
#include <Bengine\ParticleBatch2D.h>
class Zombie;

enum class GameState{PLAY,EXIT};
class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void run();
	
private:
    /// Initializes the core systems
    void initSystems();

	void initLevel();

    /// Initializes the shaders
    void initShaders();

    /// Main game loop for the program
    void gameLoop();

	void updateAgents(float deltaTime);
	void updateBullets(float deltaTime);
   
	void checkVictory();
	/// Handles input processing
    void processInput();

    /// Renders the game
    void drawGame();

	void addBlood(glm::vec2& position, int numParticles);

	void drawHud();
    /// Member Variables
    Bengine::Window _window; ///< The game window
    
    Bengine::GLSLProgram _textureProgram; ///< The shader program

    Bengine::InputManager _inputManager; ///< Handles input

    Bengine::Camera2D _camera; ///< Main Camera
	Bengine::Camera2D _hudCamera;

	Bengine::SpriteBatch _hudSpriteBatch;
	Bengine::ParticleEngine2D m_particleEngine;
	Bengine::ParticleBatch2D* m_bloodParticleBatch;

	std::vector<Level*> _levels; // vector of all levels
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	float _fps;
	int _currentLevel;

	Player* _player;
	int _numZombiesKilled;
	int _numHumansKilled;
	std::vector<Human*> _humans;
	std::vector<Zombie *> _zombies;
	std::vector<Bullet> _bullets;
	Bengine::SpriteBatch _agentSpriteBatch;
	Bengine::SpriteFont* _spriteFont;
	Bengine::AudioEngine m_audioEngine;
};

