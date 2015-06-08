#pragma once
#include <map>
#include "GLTexture.h"
#include <iostream>
#include "TextureCache.h"
#include "ImageLoader.h"
namespace Bengine{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string texturePath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};

}