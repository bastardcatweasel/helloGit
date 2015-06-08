#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>
namespace Bengine{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void draw();

		void init(int x, int y, int width, int height, std::string texturePath);
	private:

		int _x;
		int _y;
		int _width;
		int _height;
		GLuint _vboID;
		GLTexture _texture;
	};

}