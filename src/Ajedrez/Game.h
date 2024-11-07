#ifndef __GAME__
#define __GAME__

#include "GameStateMachine.h"
#include "SDL.h"

static const std::string FILES_PATH = "../../bin/Assets/";

enum posicion_equipo
{
	Arriba, Abajo
};

/* Clase singleton para la gestión del juego */
class Game
{
public:

	/* Devuelve la instancia */
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}


	/* Inicializa SDL y crea la ventana y el renderer */
	bool Init(const char* title, int xpos, int ypos, 
		int width, int height, bool fullscreen);

	/* Lee el input del usuario */
	void HandleInput();
	/* Actualiza la lógica y las físicas del juego */
	void Update();
	/* Pinta el estado actual del juego en la ventana */
	void Render();
	/* Limpia el código y cierra el juego */
	void Clean();

	/* ¿Está el juego ejecutándose? */
	bool Running() { return m_bRunning; }

	/* Cierra el juego */
	inline void Quit() { SDL_Quit(); }

	/* Getters */
	SDL_Renderer* GetRenderer() const { return m_pRenderer; }
	GameStateMachine* GetStateMachine() { return m_pGameStateMachine; }


private:
	Game() {}
	~Game() {}

	// Variables (g = global, m = member, p = pointer, b = bool, s = static)
	static Game* s_pInstance;

	// SDL
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	/* Máquina de estados finita */
	GameStateMachine* m_pGameStateMachine;
};


#endif /* defined(__Game__) */