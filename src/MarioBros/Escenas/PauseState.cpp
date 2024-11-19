#include "PauseState.h"

#include "../../Kepri2D/Game.h"
#include "../../Kepri2D/InputHandler.h"
#include "../../Kepri2D/StateParser.h"

#include "MainMenuState.h"

#include <iostream>


const std::string PauseState::s_PauseID = "PAUSE";

void PauseState::Update()
{
	for (GameObject* o : m_gameObjects)
		o->Update();
}
void PauseState::Render()
{
	for (GameObject* o : m_gameObjects)
		o->Draw();
}
bool PauseState::OnEnter()
{
	// Lectura del estado actual del XML
	StateParser stateParser;
	stateParser.ParseState("pause.xml", s_PauseID, &m_gameObjects, &m_textureIDList);

	// Añade los callbacks a la lista
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_resumePlay);
	m_callbacks.push_back(s_pauseToMenu);

	// Asigna los callbacks a los botones
	SetCallbacks(m_callbacks);

	std::cout << "entering PauseState\n";
	return true;
}

void PauseState::s_resumePlay()
{
	// Volver al PlayState
	Game::Instance()->GetStateMachine()->PopState();
}

void PauseState::s_pauseToMenu()
{
	Game::Instance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void PauseState::SetCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	if (!m_gameObjects.empty())
	{
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			// if they are of type MenuButton then assign a callback based on the id passed in from the file
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			if (pButton != nullptr) //duck typing
			{
				pButton->SetCallback(callbacks[pButton->GetCallbackID()]);
			}
		}
	}
}