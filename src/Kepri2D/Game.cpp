#include "Game.h"

#include <iostream>
#include "InputHandler.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "GameObjectFactory.h"
#include "Camera.h"
#include "SDL_ttf.h"

Game* Game::s_pInstance = 0;

bool Game::Init(const char* title, int xpos, int ypos, 
	int width, int height, bool fullscreen)
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
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		// Si la ventana se crea bien, creamos el renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				//SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
				SDL_SetRenderDrawColor(m_pRenderer, 80, 120, 210, 255);
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

	// Inicializar la librería de texto
	if (TTF_Init() >= 0)
		std::cout << "SDL_ttf initialized\n";
	else
	{
		std::cout << "SDL_ttf init fail\n";
		return false;
	}

	// Dimensiones de la ventana
	m_gameWidth = width;
	m_gameHeight = height;

	// Iniciar el InputHandler
	InputHandler::Instance()->InitialiseJoysticks();

	// Forzamos a que la cámara se inicie
	Camera* cam = Camera::Instance();

	// Lo mismo con la máquina de estados
	m_pGameStateMachine = GameStateMachine::Instance();


	std::cout << "init success\n";
	m_bRunning = true;

	return true;
}

void Game::HandleInput()
{
	// Eventos de mandos
	InputHandler::Instance()->Update();
}


void Game::Update()
{
	// Actualizar el estado actual
	m_pGameStateMachine->Update();
}

void Game::Render()
{
	// Limpiar la ventana con ese color
	SDL_RenderClear(m_pRenderer);

	// Renderizar el estado actual
	m_pGameStateMachine->Render();

	// Mostrar la ventana
	SDL_RenderPresent(m_pRenderer);
}

void Game::Clean()
{
	std::cout << "cleaning game\n";

	// limpiar todos los estados
	GameStateMachine::Instance()->Clean();

	// limpiar demás managers
	Camera::Instance()->Clean();
	SoundManager::Instance()->Clean();
	InputHandler::Instance()->Clean();
	TextureManager::Instance()->Clean();
	GameObjectFactory::Instance()->Clean();

	// limpiar SDL y SDL_ttf
	TTF_Quit();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit(); // cerrar todos los subsistemas

	// limpiar la instancia
	delete s_pInstance;
	s_pInstance = nullptr;
}