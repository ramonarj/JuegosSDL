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
	/* Actualiza la l�gica y las f�sicas del juego */
	void Update();
	/* Pinta el estado actual del juego en la ventana */
	void Render();
	/* Limpia el c�digo y cierra el juego */
	void Clean();

	/* �Est� el juego ejecut�ndose? */
	bool Running() { return m_bRunning; }

private:
	// Variables (g = global, m = member, p = pointer, b = bool)
	SDL_Window* m_pWindow = 0;
	SDL_Renderer* m_pRenderer = 0;
	bool m_bRunning = true;
};


#endif /* defined(__Game__) */