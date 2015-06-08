#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>

namespace Bengine{
	enum windowFlags{ INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };


	class Window
	{
	public:
		Window();
		~Window();
		int create(std::string name, int screenWidth, int screenHeight, unsigned int currentFlags);
		int getScreenWidth(){ _screenWidth; }
		int getScreenHeight(){ _screenHeight; }
		void swapBuffer();
	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;
	};

}