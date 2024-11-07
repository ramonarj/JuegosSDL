#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	SetTextureFrame(0, MOUSE_OUT);
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
		m_textureCol = MOUSE_OVER;
		// Ratón clicado sobre el botón
		if (InputHandler::Instance()->GetMouseButtonState(LEFT))
		{
			m_textureCol = CLICKED;
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