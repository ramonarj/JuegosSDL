#include "AnimatedGraphic.h"

void AnimatedGraphic::Load(const LoaderParams* pParams)
{
	GameObject::Load(pParams);
	m_numFrames = pParams->getNumFrames();
	m_animSpeed = pParams->getAnimSpeed();
}

void AnimatedGraphic::Update()
{
	// Cambio de frame
	m_textureCol = (int)(SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames;
	GameObject::Update();
}