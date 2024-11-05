#include "Pieza.h"

void Pieza::Update()
{
	// Movimiento independiente del framerate
	int nuevaY = int(((SDL_GetTicks() / 10) % 480));

	// Pruebas con vectores
	m_position += Vector2D(-1, 0.5);
}


void Pieza::Draw() 
{
	SDLGameObject::Draw();
}