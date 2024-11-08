#include "SDLGameObject.h"

#include "TextureManager.h"
#include "Game.h"

/* Llama expl�citamente a la constructora de GameObject */
void SDLGameObject::Load(const LoaderParams* pParams)
{
	m_position = Vector2D(pParams->getX(), pParams->getY());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();

	m_textureRow = 0;
	m_textureCol = 0;
}

void SDLGameObject::Update()
{
	// a = dv/dt
	m_velocity += m_acceleration;
	// v = de/dt
	m_position += m_velocity;
}

void SDLGameObject::Draw()
{
	/* Esto de invertir la imagen en funci�n de la velocidad ser� deseable seg�n 
	el juego que hagamos creo yo */
	// Entidad movi�ndose hacia la derecha
	if (m_velocity.GetX() >= 0)
	{
		TextureManager::Instance()->DrawFrame(m_textureID, (int)m_position.GetX(), (int)m_position.GetY(),
			m_width, m_height, m_textureRow, m_textureCol, Game::Instance()->GetRenderer());
	}
	// " " hacia la izquierda
	else
	{
		TextureManager::Instance()->DrawFrame(m_textureID, (int)m_position.GetX(), (int)m_position.GetY(),
			m_width, m_height, m_textureRow, m_textureCol, Game::Instance()->GetRenderer(), SDL_FLIP_HORIZONTAL);
	}
}
