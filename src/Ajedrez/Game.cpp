#include "Game.h"

#include <iostream>
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

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
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // fallo de inicializaci n del renderer
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // fallo de inicializaci n de la ventana
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // sdl no se pudo inicializar
	}

	// Iniciar el InputHandler
	InputHandler::Instance()->InitialiseJoysticks();

<<<<<<< HEAD
	// Iniciar la m quina de estados y cargar el estado del men 
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->ChangeState(new MenuState());

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

void Game::CreaEquipo(equipo_pieza equipo, posicion_equipo posicion)
{
	// Todas las piezas blancas
	for (int i = 0; i < 16; i++)
	{
		// Posici n donde ir  la pieza
		int posX = EQUIPO_X;
		int posY = (posicion == Arriba) ? EQUIPO_ARRIBA_Y : EQUIPO_ABAJO_Y;

		tipo_pieza tipo;
		if (i >= 8) //peones
		{
			tipo = Peon;
			if (posicion == Arriba)
				posY += TAM_CASILLA;
			else
				posY -= TAM_CASILLA;
		}
		else if (i < 5) 
			tipo = (tipo_pieza)(i + 1);
		else
			tipo = (tipo_pieza)(8 - i);

		SDLGameObject* pieza = new Pieza(new LoaderParams(posX + TAM_CASILLA * (i % 8), posY,
			ANCHO_PIEZA, ALTO_PIEZA, "piezas"), tipo, equipo);
		m_gameObjects.push_back(pieza);
	}
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	InputHandler::Instance()->Clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit(); // cerrar todos los subsistemas
}