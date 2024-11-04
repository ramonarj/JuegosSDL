#include "Game.h"
#include <iostream>
#include "SDL_image.h"

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


	// Cosas específicas del juego: IMAGEN (sin SDL_Image)
	// 1) Cargar un bmp en una surface y transformarlo a textura
	std::string file = "Reina.bmp";
	SDL_Surface* tempSurface = SDL_LoadBMP((ASSETS_PATH + file).c_str());
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	// 2) Establecer las dimensiones de origen y destino de la textura
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_srcRect.w, &m_srcRect.h);
	m_srcRect.x = m_srcRect.y = 0;
	m_destRect = { 0,0,m_srcRect.w, m_srcRect.h };

	// IMAGEN (con SDL_Image)
	std::string fileKing = "Caballo.png";
	tempSurface = IMG_Load((ASSETS_PATH + fileKing).c_str());
	m_pTextureKing = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	SDL_QueryTexture(m_pTextureKing, NULL, NULL, &m_srcRectKing.w, &m_srcRectKing.h);
	m_srcRectKing.x = m_srcRectKing.y = 0;
	m_destRectKing = { 100,100,m_srcRectKing.w, m_srcRectKing.h };

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
		default:
			break;
		}
	}
}

void Game::Update()
{
	m_destRect.x = (int)(m_destRect.x + 1) % 640;
	m_destRectKing.y = (int)(m_destRectKing.y + 1) % 480;
}

void Game::Render()
{
	// Limpiar la ventana con ese color
	SDL_RenderClear(m_pRenderer);

	// Renderizado de la textura
	//SDL_RenderCopy(m_pRenderer, m_pTexture, NULL, NULL);
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_srcRect, &m_destRect);
	SDL_RenderCopyEx(m_pRenderer, m_pTextureKing, &m_srcRectKing, &m_destRectKing, 0, NULL, SDL_FLIP_VERTICAL);

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