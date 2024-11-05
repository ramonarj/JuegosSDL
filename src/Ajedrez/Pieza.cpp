#include "Pieza.h"

#include "InputHandler.h"
#include <iostream>


void Pieza::HandleInput()
{
	float vel = 2;
	if (InputHandler::Instance()->JoysticksInitialised())
	{
		// Movimiento en 8 direcciones
		m_velocity.SetX(vel * InputHandler::Instance()->Xvalue(0, 1));
		m_velocity.SetY(vel * InputHandler::Instance()->Yvalue(0, 1));

		// Joystick izquierdo
		/*
		if (InputHandler::Instance()->Xvalue(0, 1) > 0 ||
			InputHandler::Instance()->Xvalue(0, 1) < 0)
		{
			m_velocity.SetX(1 * InputHandler::Instance()->Xvalue(0,1));
		}
		if (InputHandler::Instance()->Yvalue(0, 1) > 0 ||
			InputHandler::Instance()->Yvalue(0, 1) < 0)
		{
			m_velocity.SetY(1 * InputHandler::Instance()->Yvalue(0,1));
		}
		*/

		// Joystick derecho (no nos hace falta de momento)
		/*
		if (InputHandler::Instance()->Xvalue(0, 2) > 0 ||
			InputHandler::Instance()->Xvalue(0, 2) < 0)
		{
			m_velocity.SetX(1 * InputHandler::Instance()->Xvalue(0,2));
		}
		if (InputHandler::Instance()->Yvalue(0, 2) > 0 ||
			InputHandler::Instance()->Yvalue(0, 2) < 0)
		{
			m_velocity.SetY(1 * InputHandler::Instance()->Yvalue(0,2));
		}
		*/
	}
}

void Pieza::Update()
{
	/*
	// Movimiento independiente del framerate
	int nuevaY = int(((SDL_GetTicks() / 10) % 480));

	// Para el salvapantallas
	if (m_position.GetX() > 640)
		m_velocity.SetX(-m_velocity.GetX());
	else if (m_position.GetX() < 0)
		m_velocity.SetX(-m_velocity.GetX());

	if (m_position.GetY() > 480)
		m_velocity.SetY(-m_velocity.GetY());
	else if (m_position.GetY() < 0)
		m_velocity.SetY(-m_velocity.GetY());

	// Para probar la aceleración
	m_acceleration = m_velocity;
	m_acceleration.Normalize(); // vector unitario de la velocidad
	m_acceleration /= 50;
	*/


	// Mira a ver qué se ha pulsado en el mando
	HandleInput();

	// Llamada a la clase padre
	SDLGameObject::Update();
}


void Pieza::Draw() 
{
	SDLGameObject::Draw();
}