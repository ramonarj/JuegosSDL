#include "MainMenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include "PlayState.h"
#include "StateParser.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::Update()
{
	// Update de todas las entidades
	for (GameObject* o : m_gameObjects)
		o->Update();
}
void MainMenuState::Render()
{
	for (GameObject* o : m_gameObjects)
		o->Draw();
}
bool MainMenuState::OnEnter()
{
	// Carga las texturas necesarias para este estado
	if (!TextureManager::Instance()->Load("PlayButton.png", "playButton", Game::Instance()->GetRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->Load("ExitButton.png", "exitButton", Game::Instance()->GetRenderer()))
	{
		return false;
	}

	// Lectura del estado actual del XML
	StateParser stateParser;
	stateParser.ParseState("menu.xml", s_menuID, &m_gameObjects, &m_textureIDList);


	// Añade los callbacks a la lista
	m_callbacks.push_back(0); 
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu);
	
	// Crea los GameObjects y los añade a la lista
	/*
	GameObject* botonPlay = new MenuButton();
	GameObject* botonExit = new MenuButton();
	dynamic_cast<MenuButton*>(botonPlay)->Load(new LoaderParams(200, 200, 250, 104, "playButton", 1, 1, 0));
	dynamic_cast<MenuButton*>(botonExit)->Load(new LoaderParams(200, 350, 250, 93, "exitButton", 1, 2, 0));
	m_gameObjects.push_back(botonPlay);
	m_gameObjects.push_back(botonExit);
	*/

	// Asigna los callbacks a los botones
	SetCallbacks(m_callbacks);

	std::cout << "entering MenuState\n";
	return true;
}
bool MainMenuState::OnExit()
{
	// clear gameobjects
	for (GameObject* o : m_gameObjects)
		o->Clean();

	m_gameObjects.clear();
	// clear the texture manager
	for (int i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "exiting MenuState\n";
	return true;
}

void MainMenuState::s_menuToPlay()
{
	Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	Game::Instance()->Quit();
}

void MainMenuState::SetCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	if (!m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
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