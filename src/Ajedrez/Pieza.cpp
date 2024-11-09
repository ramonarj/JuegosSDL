#include "Pieza.h"

#include "InputHandler.h"
#include <iostream>
#include "Game.h"
#include "GameOverState.h"
#include "TextureManager.h"
#include "PlayState.h"


void Pieza::Load(const LoaderParams* pParams)
{
	SDLGameObject::Load(pParams);
}

void Pieza::SetContext(PlayState* pState, tipo_pieza tipo, equipo_pieza equipo, Vector2D posTablero)
{
	m_tipo = tipo;
	m_posTablero = posTablero;

	m_textureCol = tipo;
	m_textureRow = equipo;

	m_playState = pState;
}


void Pieza::HandleInput()
{
	// Vemos si nos han clicado
	if (InputHandler::Instance()->GetMouseButtonState(LEFT))
	{
		float mouseX = InputHandler::Instance()->GetMousePosition()->GetX();
		float mouseY = InputHandler::Instance()->GetMousePosition()->GetY();
		float posX = m_position.GetX();
		float posY = m_position.GetY();

		// Comprobar si se está clicando en la pieza
		if (mouseX > posX && mouseX < posX + m_width && 
			mouseY > posY && mouseY < posY + m_height)
		{
			//std::cout << "Clicado en pieza de " << m_posTablero.GetX() << ", " << m_posTablero.GetY() << ")\n";
			m_playState->PiezaSeleccionada(this);

			// Información de depuración
			std::string equipo = (m_textureRow == 0) ? "blanco" : "negro";
			std::cout << m_tipo << " " << equipo << std::endl;
		}
	}
}

void Pieza::Update()
{
	// Mira a ver qu  se ha pulsado en el mando
	HandleInput();

	// Llamada a la clase padre
	SDLGameObject::Update();
}


void Pieza::Draw() 
{
	SDLGameObject::Draw();
}

bool Pieza::DentroTablero(Vector2D pos)
{
	return (pos.GetX() > 0 && pos.GetX() < 8 && pos.GetY() > 0 && pos.GetY() < 8);
}