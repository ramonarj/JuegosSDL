#include "Game.h"

bool Game::Init(const char* title, int xpos, int ypos, int
	height, int width, int flags)
{
	// Inicializar todos los subsistemas
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		// Si todo va bien, creamos la ventana
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,
			height, width, flags);
		// Si la ventana se crea bien, creamos el renderer
		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
	}
	else
	{
		return false; // sdl no se pudo inicializar
	}
	return true;
}

void Game::HandleInput(){}

void Game::Update(){}

void Game::Render()
{
	// Establecer el color de la ventana (r,g,b,a)
	SDL_SetRenderDrawColor(m_pRenderer, 0, 127, 0, 255);
	// Limpiar la ventana con ese color
	SDL_RenderClear(m_pRenderer);
	// Mostrar la ventana
	SDL_RenderPresent(m_pRenderer);
}

void Game::Clean()
{
	// limpiar SDL
	SDL_Quit();
}