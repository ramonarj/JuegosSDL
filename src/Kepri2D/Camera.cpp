#include "Camera.h"

#include "Game.h"
#include <iostream>

Camera* Camera::s_pInstance = 0;


const Vector2D Camera::GetPosition() const
{
	if (m_pTarget != nullptr)
	{
		Vector2D pos(m_pTarget->GetX() - (Game::Instance()->GetGameWidth() / 2), 0);
		if (pos.GetX() < 0)
		{
			pos.SetX(0);
		}
		return pos;
	}
	return m_position;
}

void Camera::Update(Vector2D velocity)
{
	m_position += velocity;
	// limites
	//if (m_position.GetX() < 0)
	//{
	//	m_position.SetX(0);
	//}
}