#include "Game.h"

#include <iostream>
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"
#include <fstream>

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


	// Iniciar la m quina de estados y cargar el estado del men 
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->ChangeState(new MenuState());


	std::cout << "init success\n";
	m_bRunning = true;

	return true;
}

void Game::HandleInput()
{
	// Gestor de eventos
	InputHandler::Instance()->Update();

	if(InputHandler::Instance()->GetMouseButtonState(LEFT) && m_piezaSeleccionada != nullptr)
	{
		std::cout << "ee";
	}
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


void Game::LeeTablero(std::string fileName)
{
	std::ifstream archivo(FILES_PATH + fileName);
	if (archivo.is_open())
	{
		for (int i = 0; i < 8; i++)
		{
			// Leemos una l nea (descarta el salto de l nea del final)
			std::string fila;
			std::getline(archivo, fila);
			for (int j = 0; j < 8; j++)
			{
				equipo_pieza equipo;
				int tipoPieza = fila[j * 2];
				// No hay nada (salimos)
				if (tipoPieza == '0')
					break;
				// Pieza negra
				if (tipoPieza > '6')
				{
					equipo = Negras;
					tipoPieza -= 'a';
				}
				// Pieza blanca
				else
				{
					equipo = Blancas;
					tipoPieza -= '1';
				}
					
				//int tipoPieza = fila[j * 2] - '0' - 1;

				// Crea la pieza con la informaci n del archivo
				m_tablero[i][j] = new Pieza(new LoaderParams(BORDE_TABLERO + j*TAM_CASILLA, BORDE_TABLERO + i*TAM_CASILLA, 
					ANCHO_PIEZA, ALTO_PIEZA, "piezas"),  (tipo_pieza)tipoPieza, equipo, Vector2D(i, j));
				// La a ade a los GO
				m_gameObjects.push_back(m_tablero[i][j]);
			}
		}
		// De qui n es el turno ahora
		std::string turnoStr;
		std::getline(archivo, turnoStr);
		m_turno = (equipo_pieza)(turnoStr[0] - '0');
	}
	archivo.close();
}

void Game::PiezaSeleccionada(Pieza* pieza)
{
	m_piezaSeleccionada = pieza;
	m_seleccion->SetActive(true);
	m_seleccion->SetPosition(pieza->GetPosition());
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	for(SDLGameObject* go : m_gameObjects)
	{
		delete go;
		go = nullptr;
	}

	InputHandler::Instance()->Clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit(); // cerrar todos los subsistemas
}