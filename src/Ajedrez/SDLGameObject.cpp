#include "SDLGameObject.h"

#include "TextureManager.h"
#include "Game.h"

/* Llama explícitamente a la constructora de GameObject */
SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams)
{
	m_x = pParams->getX();
	m_y = pParams->getY();

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();

	m_textureRow = 0;
	m_textureCol = 0;
}

void SDLGameObject::Draw()
{
	TextureManager::Instance()->DrawFrame(m_textureID, m_x, m_y,
		m_width, m_height, m_textureRow, m_textureCol, Game::Instance()->GetRenderer());
}
