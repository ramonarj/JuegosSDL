#include "AnimatedGraphic.h"

void AnimatedGraphic::Update()
{
	// Cambio de frame
	m_textureCol = (int)(SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames;
	SDLGameObject::Update();
}