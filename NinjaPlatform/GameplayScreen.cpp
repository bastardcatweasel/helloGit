#include "GameplayScreen.h"
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <Bengine\IMainGame.h>
//#include <Bengine\IMainGame.cpp>

GameplayScreen::GameplayScreen() {
}

GameplayScreen::~GameplayScreen() {

}

int GameplayScreen::getNextScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const {
    return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::build() {
}

void GameplayScreen::destroy() {
}

void GameplayScreen::onEntry() {

}

void GameplayScreen::onExit() {
}

void GameplayScreen::update() {
    checkInput();
	
}
 
void GameplayScreen::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void GameplayScreen::checkInput(){
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->Bengine::IMainGame::onSDLEvent(evnt);
	}
}