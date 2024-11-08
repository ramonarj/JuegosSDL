#include "MenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include "PlayState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::Update()
{
	// Update de todas las entidades
	for (GameObject* o : m_gameObjects)
		o->Update();
}
void MenuState::Render()
{
	for (GameObject* o : m_gameObjects)
		o->Draw();
}
bool MenuState::OnEnter()
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
	
	// Crea los GameObjects y los añade a la lista
	GameObject* botonPlay = new MenuButton(new LoaderParams(200, 200, 250, 104, "playButton"), s_menuToPlay);
	GameObject* botonExit = new MenuButton(new LoaderParams(200, 350, 250, 93, "exitButton"), s_exitFromMenu);
	m_gameObjects.push_back(botonPlay);
	m_gameObjects.push_back(botonExit);

	std::cout << "entering MenuState\n";
	return true;
}
bool MenuState::OnExit()
{
	for (GameObject* o : m_gameObjects)
		o->Clean();

	m_gameObjects.clear();
	TextureManager::Instance()->ClearFromTextureMap("playButton");

	std::cout << "exiting MenuState\n";
	return true;
}

void MenuState::s_menuToPlay()
{
	Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
	Game::Instance()->Quit();
}