#include "Game.h"

#include <iostream>
#include "SDL_image.h"
#include "TextureManager.h"
#include "InputHandler.h"

Game* Game::s_pInstance = 0;

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

	// Iniciar el InputHandler
	InputHandler::Instance()->InitialiseJoysticks();

	// Carga de recursos con TextureManager
	TextureManager::Instance()->Load("Piezas.png", "piezas", m_pRenderer);

	// Inicializar GameObjects y añadirlos a la lista
	LoaderParams* pPiezaParams = new LoaderParams(350, 350, 46, 62, "piezas");
	piezaViva = new Pieza(pPiezaParams);
	m_gameObjects.push_back(piezaViva);


	return true;
}

void Game::HandleInput()
{
	// Eventos de mandos
	InputHandler::Instance()->Update();


	// Otros eventos
	/*
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
				piezaCambiante->SetTextureFrame(frameRow, frameCol);
				break;
			case SDLK_LEFT:
				frameRow = (frameRow + 1) % 2;
				piezaCambiante->SetTextureFrame(frameRow, frameCol);
				break;
			default:
				break;
			}

		default:
			break;
		}
	}
	*/

}


void Game::Update()
{
	// Actualizar cada uno de los GameObjects
	for (GameObject* o : m_gameObjects)
		o->Update();
}

void Game::Render()
{
	// Limpiar la ventana con ese color
	SDL_RenderClear(m_pRenderer);

	// Renderizar cada uno de los GameObjects
	for (GameObject* o : m_gameObjects)
		o->Draw();

	// Mostrar la ventana
	SDL_RenderPresent(m_pRenderer);
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	InputHandler::Instance()->Clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit(); // cerrar todos los subsistemas
}