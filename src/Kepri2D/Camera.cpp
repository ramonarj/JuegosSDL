#include "Camera.h"

#include "Game.h"
#include <iostream>

Camera* Camera::s_pInstance = 0;


const Vector2D Camera::GetPosition() const
{
	//if (m_pTarget != nullptr)
	//{
	//	Vector2D pos(m_pTarget->GetX() - (Game::Instance()->GetGameWidth() / 2), 0);
	//	if (pos.GetX() < 0)
	//	{
	//		pos.SetX(0);
	//	}
	//	return pos;
	//}
	return m_position;
}

void Camera::Update()
{
	if(m_pTarget != nullptr)
	{
		m_position = *m_pTarget;

		// Límites de la cámara
		if (m_position.GetX() < m_lowerLimit.GetX())
			m_position.SetX(m_lowerLimit.GetX());
		else if(m_position.GetX() > m_upperLimit.GetX())
			m_position.SetX(m_upperLimit.GetX());
		if (m_position.GetY() < m_lowerLimit.GetY())
			m_position.SetY(m_lowerLimit.GetY());
		else if (m_position.GetY() > m_upperLimit.GetY())
			m_position.SetY(m_upperLimit.GetY());
		//std::cout << *m_pTarget << std::endl;
	}

	// limites
	//if (m_position.GetX() < 0)
	//{
	//	m_position.SetX(0);
	//}

}

void Camera::SetBackgroundColor(uint32_t color)
{
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), color >> 24, color >> 16, color >> 8, color);
}

void Camera::Clean()
{
	if (s_pInstance != nullptr)
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}
}

Vector2D Camera::WorldToScreen(const Vector2D& pos)
{
	int screenX = Game::Instance()->GetGameWidth() / 2 + (pos.GetX() - m_position.GetX());
	int screenY = Game::Instance()->GetGameHeight() / 2 + (pos.GetY() - m_position.GetY());
	return Vector2D(screenX, screenY);
}

void Camera::SetLimits(const Vector2D& upperLeft, const Vector2D& lowerRight)
{
	m_lowerLimit = upperLeft;
	m_upperLimit = lowerRight;
}