#include "PauseState.h"

#include "MainMenuState.h"
#include <iostream>


const std::string PauseState::s_PauseID = "PAUSE";

bool PauseState::OnEnter()
{
	// Lectura del estado actual del XML
	StateParser stateParser;
	stateParser.ParseState("pause.xml", s_PauseID, &m_gameObjects, &m_textureIDList);

	Camera::Instance()->SetPosition({ 320, 240 });

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
	SoundManager::Instance()->PlaySound("clic", 0);
	SoundManager::Instance()->ResumeMusic();
	Game::Instance()->GetStateMachine()->PopState();
}

void PauseState::s_pauseToMenu()
{
	SoundManager::Instance()->PlaySound("clic", 0);
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