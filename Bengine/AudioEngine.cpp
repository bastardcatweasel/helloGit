#include "AudioEngine.h"
#include "BengineErrors.h"

namespace Bengine{

	void SoundEffect::play(int loops)
	{
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1) 
		{
			if (Mix_PlayChannel(0, m_chunk, loops) == -1)
			{
				fatalError("MixplayChannel Error: " + std::string(Mix_GetError()));
			}
		}

			
	}

	void Music::play(int loops)
	{
		if (Mix_PlayMusic(m_music, loops))
		{
			fatalError("MixplayMusic Error: " + std::string(Mix_GetError()));
		}


	


	}

	void Music::pause()
	{
		Mix_PauseMusic();
	}
	void Music::stop()
	{
		Mix_HaltMusic();
	}
	void Music::resume()
	{
		Mix_ResumeMusic();
	}
	AudioEngine::AudioEngine()
	{


	}


	AudioEngine::~AudioEngine()
	{

		destroy();
	}

	void AudioEngine::init()
	{

		if (m_isInitialized)
		{
			fatalError("tried to Initialize Audio Engine Twice");
		}
		//Initializes audio, bitwise combination of MIX_INIT_FAC, MOD, MP3, OGG, wav by default
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
		{
			fatalError("Mix_Init Error: " + std::string(Mix_GetError()));

		}

		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		{
			fatalError("Mix_OpenAudio Error: " + std::string(Mix_GetError()));
		}
		m_isInitialized = true;
		
	}
	void AudioEngine::destroy()
	{
		if (m_isInitialized)
		{
			m_isInitialized = false;
			for (auto& it : m_effectMap)
			{
				Mix_FreeChunk(it.second);
			}

			for (auto& it : m_musicMap)
			{
				Mix_FreeMusic(it.second);
			}
			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath)
	{
		//try to find music in cache
		auto it = m_effectMap.find(filePath);

		SoundEffect effect;

		if (it == m_effectMap.end())
		{
			//failed to find it
			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());

			if (chunk == nullptr)
			{
				fatalError("MixLoadWAV Error: " + std::string(Mix_GetError()));
			}

			effect.m_chunk = chunk;
			m_effectMap[filePath] = chunk;
		}
		else
		{
			//its already there
			effect.m_chunk = it->second;
		}

		return effect;
	}
	Music AudioEngine::loadMusic(const std::string& filePath)
	{
		//try to find music in cache
		auto it = m_musicMap.find(filePath);

		Music music;

		if (it == m_musicMap.end())
		{
			//failed to find it
			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());

			if (mixMusic == nullptr)
			{
				fatalError("MixLoadMUSError: " + std::string(Mix_GetError()));
			}

			music.m_music = mixMusic;
			m_musicMap[filePath] = mixMusic;
		}
		else
		{
			//its already there
			music.m_music = it->second;
		}

		return music;
	}
}