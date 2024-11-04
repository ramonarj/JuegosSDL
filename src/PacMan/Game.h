#ifndef __GAME__
#define __GAME__

#include "SDL.h"

class Game
{
public:
	Game(){}
	~Game(){}

	/* Inicializa SDL y crea la ventana y el renderer */
	bool Init(const char* title, int xpos, int ypos, int
		height, int width, int flags);

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

private:
	// Variables (g = global, m = member, p = pointer, b = bool)
	SDL_Window* m_pWindow = 0;
	SDL_Renderer* m_pRenderer = 0;
	bool m_bRunning = true;
};


#endif /* defined(__Game__) */