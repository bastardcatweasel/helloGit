#pragma once
#include <unordered_map>
#include <glm\glm.hpp>

namespace Bengine {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();




		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);
		bool isKeyPressed(unsigned int keyID);
		
		//setter
		void setMouseCoords(float x, float y);

		//getter
		const glm::vec2 getMouseCoords(){return _mouseCoords;}

	private:
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;


	};

}