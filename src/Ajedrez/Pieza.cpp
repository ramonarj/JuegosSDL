#include "Pieza.h"

#include "InputHandler.h"
#include <iostream>
#include "Game.h"

void Pieza::InputConMando()
{
	float vel = 3;
	if (InputHandler::Instance()->JoysticksInitialised())
	{
		// Movimiento en 8 direcciones con el joystick
		m_velocity.SetX(vel * InputHandler::Instance()->Xvalue(0, 1));
		m_velocity.SetY(vel * InputHandler::Instance()->Yvalue(0, 1));

		// Movimiento discreto con los triggers
		if (InputHandler::Instance()->GetButtonState(0, 6))
			m_position -= Vector2D(20, 0);
		if (InputHandler::Instance()->GetButtonState(0, 7))
			m_position += Vector2D(20, 0);

		// Cambio de color con un bot�n
		if (InputHandler::Instance()->GetButtonState(0, 0))
		{
			frameRow = (frameRow + 1) % 2;
			SetTextureFrame(frameRow, frameCol);
		}

		// Cambio de pieza con la cruceta
		if (InputHandler::Instance()->GetHat(0) == 2)
		{
			frameCol = (frameCol + 1) % 6;
			SetTextureFrame(frameRow, frameCol);
		}


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

void Pieza::InputConRaton()
{
	// Con el clic izquierdo mantenemos la pieza parada hasta soltarlo
	if(InputHandler::Instance()->GetMouseButtonState(LEFT))
	{
		if(m_velocity.Length() > 0)
		{
			prevVel = m_velocity;
			
		}
		m_velocity = Vector2D(0, 0);
		m_acceleration = Vector2D(0, 0);
	}
	else if (m_velocity.Length() < 0.1)
	{
		m_velocity = prevVel;
	}

	// Con el clic derecho reseteamos la velocidad y aceleraci�n
	if(InputHandler::Instance()->GetMouseButtonState(RIGHT))
	{
		std::cout << "Clic derecho" << std::endl;
		m_velocity.Normalize();
		m_acceleration = Vector2D(0, 0);
	}

	// Con el bot�n del medio cambiamos el color
	if(InputHandler::Instance()->GetMouseButtonState(MIDDLE))
	{
		m_position = *InputHandler::Instance()->GetMousePosition();
	}
}

void Pieza::InputConTeclado()
{
	// Con las teclas 1-6 cambiamos de pieza
	int uno = SDL_SCANCODE_1;
	for (int i = 0; i < 6; i++)
	{
		if (InputHandler::Instance()->IsKeyDown(SDL_Scancode(uno + i)))
		{
			frameCol = i;
			SetTextureFrame(frameRow, frameCol);
		}
	}

	// Con la barra espaciadora cambiamos el color
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		frameRow = (frameRow + 1) % 2;
		SetTextureFrame(frameRow, frameCol);
	}
}

void Pieza::HandleInput()
{
	//InputConMando();
	InputConTeclado();
	InputConRaton();
}

void Pieza::Update()
{
	// Mira a ver qu� se ha pulsado en el mando
	HandleInput();

	// Movimiento independiente del framerate
	//int nuevaY = int(((SDL_GetTicks() / 10) % 480));

	// Para el salvapantallas
	
	if (m_position.GetX() > 640)
		m_velocity.SetX(-m_velocity.GetX());
	else if (m_position.GetX() < 0)
		m_velocity.SetX(-m_velocity.GetX());

	if (m_position.GetY() > 480)
		m_velocity.SetY(-m_velocity.GetY());
	else if (m_position.GetY() < 0)
		m_velocity.SetY(-m_velocity.GetY());

	// Para probar la aceleraci�n
	m_acceleration = m_velocity;
	m_acceleration.Normalize(); // vector unitario de la velocidad
	m_acceleration /= 50;
	


	// Llamada a la clase padre
	SDLGameObject::Update();
}


void Pieza::Draw() 
{
	SDLGameObject::Draw();
}