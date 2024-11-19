#include "SoundManager.h"

#include "SDL_mixer.h"
#include <iostream>

SoundManager* SoundManager::s_pInstance = 0;

SoundManager::SoundManager()
{
	// Iniciar el sistema de audio (con 22050Hz se escucha regular)
	Mix_OpenAudio(44000, AUDIO_S16, 2, 4096);
}

bool SoundManager::Load(std::string fileName, std::string id, sound_type type)
{
	fileName = SOUNDS_PATH + fileName;

	// Archivo de música
	if (type == SOUND_MUSIC)
	{
		Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
		if (pMusic == 0) //error
		{
			std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_music[id] = pMusic;
		return true;
	}
	// Archivo de SFX
	else if (type == SOUND_SFX)
	{
		// Aunque se llame "LoadWAV", permite cargar .mp3
		Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
		if (pChunk == 0) //error
		{
			std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
			return false;
		}
		m_sfxs[id] = pChunk;
		return true;
	}
	return false;
}

void SoundManager::PlaySound(std::string id, int loop)
{
	// el '-1' reproduce el sonido en un canal disponible cualquiera
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void SoundManager::PlayMusic(std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}


void SoundManager::PauseMusic()
{
	Mix_PauseMusic();
}

void SoundManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

void SoundManager::StopMusic()
{
	Mix_HaltMusic();
}

void SoundManager::ChangeVolume(int vol)
{
	// Convertimos el rango 0-100 al rango 0-128 que usa SDL_Mixer
	vol = int(vol * MIX_MAX_VOLUME / 100.0);

	Mix_MasterVolume(vol);
	Mix_VolumeMusic(vol);
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}