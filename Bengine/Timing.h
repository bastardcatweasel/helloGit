#pragma once
namespace Bengine{




	class FpsLimiter
	{
		
	public:

		FpsLimiter();
		
		
		void init(float maxFPS);

		void setMaxFPS(float maxFPS);
		
		

		void begin();

		float end(); //return FPS

	private:

		float _maxFPS;
		unsigned int _startTicks;
		float _fps;
		float _frameTime;
		void calculateFPS();
	};







}