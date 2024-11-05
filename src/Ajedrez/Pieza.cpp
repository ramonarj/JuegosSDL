#include "Pieza.h"

void Pieza::Update()
{
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

	// Llamada a la clase padre
	SDLGameObject::Update();
}


void Pieza::Draw() 
{
	SDLGameObject::Draw();
}