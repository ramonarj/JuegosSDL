#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams, void(*callback)()) : SDLGameObject(pParams), m_callback(callback)
{
	m_textureCol = MOUSE_OUT;
}

void MenuButton::Update()
{
	Vector2D* pMousePos = InputHandler::Instance()->GetMousePosition();

	// Comprobamos que el rat�n est� dentro de las lindes del bot�n
	if (pMousePos->GetX() < (m_position.GetX() + m_width)
		&& pMousePos->GetX() > m_position.GetX()
		&& pMousePos->GetY() < (m_position.GetY() + m_height)
		&& pMousePos->GetY() > m_position.GetY())
	{
		// Rat�n clicado sobre el bot�n
		if (InputHandler::Instance()->GetMouseButtonState(LEFT) && m_bReleased)
		{
			m_textureCol = CLICKED;
			if(m_callback != nullptr) // a�adido por seguridad
				m_callback(); // call our callback function
			m_bReleased = false;
		}
		else if (!InputHandler::Instance()->GetMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_textureCol = MOUSE_OVER;
		}
	}
	// Rat�n fuera de las lindes
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