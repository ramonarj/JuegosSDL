#include "GameOverState.h"

#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include "PlayState.h"
#include "MainMenuState.h"
#include "InputHandler.h"
#include "StateParser.h"

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

	/*
	// Carga las texturas necesarias para este estado
	if (!TextureManager::Instance()->Load("RestartButton.png", "restartButton", Game::Instance()->GetRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->Load("MenuButton.png", "menuButton", Game::Instance()->GetRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->Load("GameOver.png", "gameover", Game::Instance()->GetRenderer()))
	{
		return false;
	}
	
	// Crea los GameObjects y los añade a la lista
	GameObject* botonRestart = new MenuButton();
	GameObject* botonMenu = new MenuButton();
	GameObject* gameoverImage = new AnimatedGraphic();
	dynamic_cast<MenuButton*>(botonRestart)->Load(new LoaderParams(200, 200, 200, 80, "restartButton", 1, 1, 0));
	dynamic_cast<MenuButton*>(botonMenu)->Load(new LoaderParams(200, 350, 200, 80, "menuButton", 1, 2, 0));
	dynamic_cast<AnimatedGraphic*>(gameoverImage)->Load(new LoaderParams(200, 100, 190, 30, "gameover", 2, 0, 2));
	m_gameObjects.push_back(botonRestart);
	m_gameObjects.push_back(botonMenu);
	m_gameObjects.push_back(gameoverImage);

	*/

	// Añade los callbacks a la lista
	m_callbacks.push_back(0);
	m_callbacks.push_back(s_restartPlay);
	m_callbacks.push_back(s_gameoverToMenu);

	// Asigna los callbacks a los botones
	SetCallbacks(m_callbacks);

	std::cout << "entering GameOverState\n";
	return true;
}
bool GameOverState::OnExit()
{
	for (GameObject* o : m_gameObjects)
		o->Clean();

	m_gameObjects.clear();
	// clear the texture manager
	for (size_t i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
	}
	// reset the mouse button states to false
	InputHandler::Instance()->Reset();

	std::cout << "exiting GameOverState\n";
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