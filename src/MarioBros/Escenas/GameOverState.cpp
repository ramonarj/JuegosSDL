#include "GameOverState.h"

#include "PlayState.h"
#include "MainMenuState.h"

#include <iostream>

const std::string GameOverState::s_gameoverID = "GAMEOVER";

void GameOverState::Update()
{
	for (GameObject* o : m_gameObjects)
		o->Update();
}
void GameOverState::Render()
{
	for (GameObject* o : m_gameObjects)
		o->Draw();
}
bool GameOverState::OnEnter()
{
	// Lectura del estado actual del XML
	StateParser stateParser;
	stateParser.ParseState("gameover.xml", s_gameoverID, &m_gameObjects, &m_textureIDList);

	// Añade los callbacks a la lista
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_restartPlay);
	m_callbacks.push_back(s_gameoverToMenu);

	// Asigna los callbacks a los botones
	SetCallbacks(m_callbacks);

	std::cout << "entering GameOverState\n";
	return true;
}

void GameOverState::s_restartPlay()
{
	// Volver al PlayState
	Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

void GameOverState::s_gameoverToMenu()
{
	Game::Instance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void GameOverState::SetCallbacks(const std::vector<Callback>& callbacks)
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