#include "CanvasObject.h"

#include "TextureManager.h"
#include "Game.h"

void CanvasObject::Draw()
{
	// Exactamente lo mismo que el GameObject, solo que los objetos del canvas no 
	// necesitan transformar sus coordenadas, porque ya están en términos de la ventana
	TextureManager::Instance()->DrawFrame(m_textureID, m_position.GetX(), m_position.GetY(),
		m_width, m_height, m_frameWidth, m_frameHeight, m_textureRow, m_textureCol,
		Game::Instance()->GetRenderer(), m_angle, m_alpha);
}