#ifndef __SOUNDMANAGER__
#define __SOUNDMANAGER__

#include <string>
#include <map>
#include "SDL_mixer.h"
#include "checkML.h"

// Ruta a los sonidos desde la carpeta src/
const std::string SOUNDS_PATH = "../../bin/assets/sounds/";

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

/* Clase singleton para gestionar la música y sonidos con SDL_Mixer */
class SoundManager
{
public:

	/* Acceso a la instancia del singleton */
	static SoundManager* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new SoundManager();
		return s_pInstance;
	}

	/* Carga un archivo de sonido */
	bool Load(std::string fileName, std::string id, sound_type type);

	/* Reproduce un sonido un número de veces dado (-1 para loop continuo) */
	void PlaySound(std::string id, int loop);
	/* Reproduce una canción un número de veces dado (-1 para loop continuo) */
	void PlayMusic(std::string id, int loop);

	// Para destruir la instancia
	void Clean() { delete s_pInstance; s_pInstance = nullptr; }

private:
	SoundManager();
	~SoundManager();
	/* Constructora por copia */
	SoundManager(const SoundManager&);
	/* Operador de asignación */
	SoundManager& operator=(const SoundManager&);

	/* Instancia */
	static SoundManager* s_pInstance;

	/* Diccionario de sonidos */
	std::map<std::string, Mix_Chunk*> m_sfxs;
	/* Diccionario de canciones */
	std::map<std::string, Mix_Music*> m_music;
};

#endif/* defined(__SoundManager__) */