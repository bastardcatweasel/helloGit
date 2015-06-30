#pragma once
#include <iostream>
#include <SDL/SDL.h>
#include <Bengine\IMainGame.h>

#include <Bengine\IGameScreen.h>

class Bengine::IMainGame;

// Our custom gameplay screen that inherits from the IGameScreen
class GameplayScreen : public Bengine::IGameScreen {
public:
	GameplayScreen();
	~GameplayScreen();

    virtual int getNextScreenIndex() const override;

    virtual int getPreviousScreenIndex() const override;

    virtual void build() override;

    virtual void destroy() override;

    virtual void onEntry() override;

    virtual void onExit() override;

    virtual void update() override;

    virtual void draw() override;
 
private:
	void checkInput();

};

