#include "GameObject.h"

#include "TextureManager.h"
#include "Game.h"
#include "Camera.h"


/* Llama explícitamente a la constructora de GameObject */
void GameObject::Load(const LoaderParams* pParams)
{
	m_position = Vector2D((float)pParams->getX(), (float)pParams->getY());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_frameWidth = pParams->getFrameWidth();
	m_frameHeight = pParams->getFrameHeight();

	m_textureID = pParams->getTextureID();

	m_textureRow = 0;
	m_textureCol = 0;
}

void GameObject::Update()
{
	// a = dv/dt
	m_velocity += m_acceleration;
	// v = de/dt
	m_position += m_velocity;
}

void GameObject::Draw()
{
	// Transformamos las coordenadas reales del GameObject en píxeles en rango de nuestra ventana
	// (de acuerdo a la posición de la cámara)
	Vector2D screenPos = Camera::Instance()->WorldToScreen(m_position);
	/* Esto de invertir la imagen en función de la velocidad será deseable según 
	el juego que hagamos creo yo */
	// Entidad moviéndose hacia la derecha
	if (m_velocity.GetX() >= 0)
	{
		TextureManager::Instance()->DrawFrame(m_textureID, screenPos.GetX(), screenPos.GetY(),
			m_width, m_height, m_frameWidth, m_frameHeight, m_textureRow, m_textureCol,  
			Game::Instance()->GetRenderer(), m_angle, m_alpha);
	}
	// " " hacia la izquierda
	else
	{
		TextureManager::Instance()->DrawFrame(m_textureID, screenPos.GetX(), screenPos.GetY(),
			m_width, m_height, m_frameWidth, m_frameHeight, m_textureRow, m_textureCol,
			Game::Instance()->GetRenderer(), m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
	}
}