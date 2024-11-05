#include "GameObject.h"

#include "TextureManager.h"


void GameObject::Load(int x, int y, int width, int height, std::string textureID)
{
	m_x = x;
	m_y = y;

	m_width = width;
	m_height = height;

	m_textureID = textureID;

	// Valores por defecto
	m_textureCol = 0;
	m_textureRow = 0;
}

void GameObject::Draw(SDL_Renderer* pRenderer)
{
	TextureManager::Instance()->DrawFrame(m_textureID, m_x, m_y,
		m_width, m_height, m_textureRow, m_textureCol, pRenderer);
}