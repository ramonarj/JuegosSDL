#include "PlayState.h"

#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Pieza.h"


const std::string PlayState::s_playID = "PLAY";

void PlayState::Update()
{
	// Con el escape, salimos al menú
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->GetStateMachine()->PushState(new PauseState());
	}

	// 
	if (InputHandler::Instance()->GetMouseButtonState(LEFT) && m_piezaSeleccionada != nullptr)
	{
		std::cout << "ee";
	}

	for (SDLGameObject* o : m_gameObjects)
		if (o->IsActive())
			o->Update();
}

void PlayState::Render()
{
	for (SDLGameObject* o : m_gameObjects)
		if (o->IsActive())
			o->Draw();
}

bool PlayState::OnEnter()
{
	std::cout << "entering PlayState\n";

	// Carga de recursos con TextureManager
	TextureManager::Instance()->Load("Tablero.png", "tablero", Game::Instance()->GetRenderer());
	TextureManager::Instance()->Load("Piezas.png", "piezas", Game::Instance()->GetRenderer());
	TextureManager::Instance()->Load("Seleccion.png", "seleccion", Game::Instance()->GetRenderer());


	// Inicializar GameObjects y a adirlos a la lista
	//LoaderParams* pPiezaParams = new LoaderParams(350, 350, 46, 62, "piezas");
	m_fondoTablero = new SDLGameObject(new LoaderParams(0, 0, 500, 500, "tablero"));
	m_seleccion = new SDLGameObject(new LoaderParams(BORDE_TABLERO, BORDE_TABLERO, 55, 55, "seleccion"));
	piezaViva = new Pieza(new LoaderParams(200, 200, ANCHO_PIEZA, ALTO_PIEZA, "piezas"), Peon, Blancas, Vector2D(0, 0), this);


	m_gameObjects.push_back(m_fondoTablero);
	m_gameObjects.push_back(piezaViva);


	// Leer el tablero de archivo, crea las piezas y las a ade a la lista de GameObjects
	LeeTablero("tablero.txt");
	m_piezaSeleccionada = nullptr;

	m_gameObjects.push_back(m_seleccion);
	m_seleccion->SetActive(false);


	return true;
}

void PlayState::LeeTablero(std::string fileName)
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
					continue;
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
				Pieza* p = new Pieza(new LoaderParams(BORDE_TABLERO + j * TAM_CASILLA, BORDE_TABLERO + i * TAM_CASILLA - 10,
					ANCHO_PIEZA, ALTO_PIEZA, "piezas"), (tipo_pieza)tipoPieza, equipo, Vector2D(i, j), this);
				/*m_tablero[i][j] = new Pieza(new LoaderParams(BORDE_TABLERO + j * TAM_CASILLA, BORDE_TABLERO + i * TAM_CASILLA,
					ANCHO_PIEZA, ALTO_PIEZA, "piezas"), (tipo_pieza)tipoPieza, equipo, Vector2D(i, j));*/
				// La a ade a los GO
				//m_gameObjects.push_back(m_tablero[i][j]);
				m_gameObjects.push_back(p);
			}
		}
		// De qui n es el turno ahora
		std::string turnoStr;
		std::getline(archivo, turnoStr);
		m_turno = (equipo_pieza)(turnoStr[0] - '0');
	}
	archivo.close();
}

void PlayState::PiezaSeleccionada(Pieza* pieza)
{
	m_piezaSeleccionada = pieza;
	m_seleccion->SetActive(true);
	m_seleccion->SetPosition(pieza->GetPosition());
}

bool PlayState::OnExit()
{
	for (GameObject* o : m_gameObjects)
		o->Clean();

	m_gameObjects.clear();
	TextureManager::Instance()->ClearFromTextureMap("piezas");

	std::cout << "exiting PlayState\n";
	return true;
}