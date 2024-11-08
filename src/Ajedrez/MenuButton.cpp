#include "MenuButton.h"
#include "InputHandler.h"

void MenuButton::Load(const LoaderParams* pParams)
{
	SDLGameObject::Load(pParams);
	m_callbackID = pParams->getCallbackID();
	m_textureCol = MOUSE_OUT;
}

void MenuButton::Update()
{
	Vector2D* pMousePos = InputHandler::Instance()->GetMousePosition();

	// Comprobamos que el ratón esté dentro de las lindes del botón
	if (pMousePos->GetX() < (m_position.GetX() + m_width)
		&& pMousePos->GetX() > m_position.GetX()
		&& pMousePos->GetY() < (m_position.GetY() + m_height)
		&& pMousePos->GetY() > m_position.GetY())
	{
		// Ratón clicado sobre el botón
		if (InputHandler::Instance()->GetMouseButtonState(LEFT) && m_bReleased)
		{
			m_textureCol = CLICKED;
			if(m_callback != nullptr) // añadido por seguridad
				m_callback(); // call our callback function
			m_bReleased = false;
		}
		else if (!InputHandler::Instance()->GetMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_textureCol = MOUSE_OVER;
		}
	}
	// Ratón fuera de las lindes
	else
	{
		m_textureCol = MOUSE_OUT;
	}
}

void MenuButton::Draw()
{
	SDLGameObject::Draw();
}

void MenuButton::Clean()
{
	SDLGameObject::Clean();
}