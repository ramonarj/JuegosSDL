#include "Game.h"

#include <iostream>
#include "SDL_image.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

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
				return false; // fallo de inicializaci�n del renderer
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // fallo de inicializaci�n de la ventana
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // sdl no se pudo inicializar
	}

	// Iniciar la m�quina de estados y cargar el estado del men�
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->ChangeState(new MenuState());

	// Iniciar el InputHandler
	InputHandler::Instance()->InitialiseJoysticks();

	// Carga de recursos con TextureManager
	TextureManager::Instance()->Load("Piezas.png", "piezas", m_pRenderer);
	TextureManager::Instance()->Load("PlayButton.png", "playButton", m_pRenderer);

	std::cout << "init success\n";
	m_bRunning = true;

	return true;
}

void Game::HandleInput()
{
	// Eventos de mandos
	InputHandler::Instance()->Update();

	// Con Enter, pasamos al PlayState
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->ChangeState(new PlayState());
	}
	// Con el escape, salimos al men�
	else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		m_pGameStateMachine->ChangeState(new MenuState());
	}
}


void Game::Update()
{
	// Actualizar el estado actual
	m_pGameStateMachine->Update();

	// Actualizar cada uno de los GameObjects
	//for (GameObject* o : m_gameObjects)
	//	o->Update();
}

void Game::Render()
{
	// Limpiar la ventana con ese color
	SDL_RenderClear(m_pRenderer);

	// Renderizar el estado actual
	m_pGameStateMachine->Render();

	// Renderizar cada uno de los GameObjects
	//for (GameObject* o : m_gameObjects)
	//	o->Draw();

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