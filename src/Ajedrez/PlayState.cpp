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
#include "AnimatedGraphic.h"
#include "StateParser.h"


const std::string PlayState::s_playID = "PLAY";

void PlayState::Update()
{
	// Con el escape, salimos al menú
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->GetStateMachine()->PushState(new PauseState());
	}

	for (GameObject* o : m_gameObjects)
		if (o->IsActive())
			o->Update();
}

void PlayState::Render()
{
	for (GameObject* o : m_gameObjects)
		if (o->IsActive())
			o->Draw();
}

bool PlayState::OnEnter()
{
	// Lectura del estado actual del XML
	StateParser stateParser;
	stateParser.ParseState("chess.xml", s_playID, &m_gameObjects, &m_textureIDList);

	// Leer el tablero de archivo, crea las piezas y las a ade a la lista de GameObjects
	LeeTablero("tablero.txt");
	m_piezaSeleccionada = nullptr;

	m_seleccion = dynamic_cast<AnimatedGraphic*>(m_gameObjects[1]);
	m_seleccion->SetActive(false);

	std::cout << "entering PlayState\n";
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
				Pieza* p = new Pieza();
				p->Load(new LoaderParams(BORDE_TABLERO + j * TAM_CASILLA, BORDE_TABLERO + i * TAM_CASILLA - 10,
					ANCHO_PIEZA, ALTO_PIEZA, "piezas"));
				p->SetContext(this, (tipo_pieza)tipoPieza, equipo, Vector2D(i, j));
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
	// clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::CheckCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->GetPosition().GetX();
	rightA = p1->GetPosition().GetX() + p1->GetWidth();
	topA = p1->GetPosition().GetY();
	bottomA = p1->GetPosition().GetY() + p1->GetHeight();

	//Calculate the sides of rect B
	leftB = p2->GetPosition().GetX();
	rightB = p2->GetPosition().GetX() + p2->GetWidth();
	topB = p2->GetPosition().GetY();
	bottomB = p2->GetPosition().GetY() + p2->GetHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}