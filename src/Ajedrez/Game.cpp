#include "Game.h"

#include <iostream>
#include "SDL_image.h"
#include "TextureManager.h"

bool Game::Init(const char* title, int xpos, int ypos, 
	int height, int width, bool fullscreen)
{
	// Para la pantalla completa
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	// Inicializar todos los subsistemas
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL init success\n";
		// Si todo va bien, creamos la ventana
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// Si la ventana se crea bien, creamos el renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // fallo de inicialización del renderer
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // fallo de inicialización de la ventana
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // sdl no se pudo inicializar
	}

	std::cout << "init success\n";
	m_bRunning = true;


	// Carga de recursos con TextureManager
	TextureManager::Instance()->Load("Caballo.png", "caballo", m_pRenderer);
	TextureManager::Instance()->Load("Piezas.jpg", "piezas", m_pRenderer);

	// Inicializar GameObjects
	caballo.Load(200, 200, 100, 100, "caballo");
	piezaCambiante.Load(350, 350, 46, 62, "piezas");

	frameRow = 0;
	frameCol = 0;

	return true;
}

void Game::HandleInput()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// Cerrar la ventana (clicando en la X)
		case SDL_QUIT:
			m_bRunning = false;
			break;
		// Teclas normales (flechas)
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_RIGHT:
				frameCol = (frameCol+1) % 6;
				piezaCambiante.SetTextureFrame(frameRow, frameCol);
				break;
			case SDLK_DOWN:
				frameRow = (frameRow + 1) % 2;
				piezaCambiante.SetTextureFrame(frameRow, frameCol);
				break;
			default:
				break;
			}

		default:
			break;
		}
	}
}

void Game::Update()
{
	// Movimiento independiente del framerate
	int nuevaPosY = int(((SDL_GetTicks() / 10) % 480));
	caballo.SetPos(caballo.GetPosX(), nuevaPosY);
}

void Game::Render()
{
	// Limpiar la ventana con ese color
	SDL_RenderClear(m_pRenderer);

	// Renderizado de los GameObjects
	//SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, NULL)
	caballo.Draw(m_pRenderer);
	piezaCambiante.Draw(m_pRenderer);

	// Mostrar la ventana
	SDL_RenderPresent(m_pRenderer);
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit(); // cerrar todos los subsistemas
}