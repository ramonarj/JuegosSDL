#ifndef __GAME__
#define __GAME__

#include "SDL.h"
#include <string>
#include "TextureManager.h"

class Game
{
public:
	Game(){}
	~Game(){}

	/* Inicializa SDL y crea la ventana y el renderer */
	bool Init(const char* title, int xpos, int ypos, 
		int height, int width, bool fullscreen);

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
	// SDL
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	// Managers
	TextureManager m_textureManager;

	// Caballo
	SDL_Rect m_destRectKing;

	// Cambio de frame
	int frameCol;
	int frameRow;
};


#endif /* defined(__Game__) */