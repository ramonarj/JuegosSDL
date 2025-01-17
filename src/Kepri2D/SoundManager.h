#ifndef __SOUNDMANAGER__
#define __SOUNDMANAGER__

#include <string>
#include <map>
#include "checkML.h"

struct Mix_Chunk;
struct _Mix_Music;

// Ruta a los sonidos desde la carpeta src/
const std::string SOUNDS_PATH = "../../bin/assets/sounds/";

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

/* Clase singleton para gestionar la m�sica y sonidos con SDL_Mixer */
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

	/* Reproduce un sonido un n�mero de veces dado (-1 para loop continuo) */
	void PlaySound(std::string id, int loop);
	/* Reproduce una canci�n un n�mero de veces dado (-1 para loop continuo) */
	void PlayMusic(std::string id, int loop);

	/* Pausa la m�sica que est� sonando actualmente */
	void PauseMusic();
	/* Reanuda la m�sica que estaba sonando antes de pausarla */
	void ResumeMusic();
	/* Detiene completamente la m�sica que est� sonando actualmente */
	void StopMusic();

	/* Cambia el volumen general de la m�sica y sonidos (0 = silencio, 100 = m�ximo) */
	void ChangeVolume(int vol);

	// Para destruir la instancia
	void Clean() { delete s_pInstance; s_pInstance = nullptr; }

private:
	SoundManager();
	~SoundManager();
	/* Constructora por copia */
	SoundManager(const SoundManager&);
	/* Operador de asignaci�n */
	SoundManager& operator=(const SoundManager&);

	/* Instancia */
	static SoundManager* s_pInstance;

	/* Diccionario de sonidos */
	std::map<std::string, Mix_Chunk*> m_sfxs;
	/* Diccionario de canciones */
	std::map<std::string, _Mix_Music*> m_music;
};

#endif/* defined(__SoundManager__) */