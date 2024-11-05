#include "Pieza.h"

void Pieza::Update()
{
	// Movimiento independiente del framerate
	m_y = int(((SDL_GetTicks() / 10) % 480));
}


void Pieza::Draw() 
{
	SDLGameObject::Draw();
}