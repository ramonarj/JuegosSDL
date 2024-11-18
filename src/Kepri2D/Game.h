#ifndef __GAME__
#define __GAME__

#include "GameStateMachine.h"
#include "../../dependencies/SDL2-2.30.9/include/SDL.h"

// Esto es por si quiero usar un main normal y no la macro de SDL
#undef main

/* Clase singleton para la gesti�n del juego */
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
	/* Actualiza la l�gica y las f�sicas del juego */
	void Update();
	/* Pinta el estado actual del juego en la ventana */
	void Render();
	/* Limpia el c�digo y cierra el juego */
	void Clean();

	/* �Est� el juego ejecut�ndose? */
	bool Running() { return m_bRunning; }

	/* Cierra el juego */
	inline void Quit() { m_bRunning = false; }

	/* Getters */
	inline SDL_Renderer* GetRenderer() const { return m_pRenderer; }
	inline GameStateMachine* GetStateMachine() { return m_pGameStateMachine; }
	/* Anchura de la ventana, en p�xeles */
	inline int GetGameWidth() { return m_gameWidth; }
	/* Altura de la ventana, en p�xeles */
	inline int GetGameHeight() { return m_gameHeight; }

	/* Wrappers de SDL */
	/* N�mero de milisegundos desde que se inici� el juego */
	inline Uint32 GetTicks() { return SDL_GetTicks(); }

	inline void DelayFor(Uint32 ms) { SDL_Delay(ms); }

	inline const char* GetError() { return SDL_GetError(); }

private:
	/* Constructora por defecto */
	Game() : m_bRunning(false), m_pRenderer(nullptr), m_pWindow(nullptr), 
		m_gameWidth(0), m_gameHeight(0), m_pGameStateMachine (nullptr) {}
	~Game() {}

	// Variables (g = global, m = member, p = pointer, b = bool, s = static)
	static Game* s_pInstance;

	// SDL
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	// dimensiones de la ventana
	int m_gameWidth;
	int m_gameHeight;

	/* M�quina de estados finita */
	GameStateMachine* m_pGameStateMachine;
};


#endif /* defined(__Game__) */