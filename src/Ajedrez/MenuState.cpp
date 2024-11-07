#include "MenuState.h"

#include "TextureManager.h"
#include "Game.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::Update()
{
	// Update de todas las entidades
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update();
	}
}
void MenuState::Render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Draw();
	}
}
bool MenuState::OnEnter()
{
	// Carga las texturas necesarias para este estado
	if (!TextureManager::Instance()->Load("PlayButton.png", "playButton", Game::Instance()->GetRenderer()))
	{
		return false;
	}
	
	// Crea los GameObjects y los añade a la lista
	GameObject* botonPlay = new MenuButton(new LoaderParams(200, 200, 250, 104, "playButton"));
	m_gameObjects.push_back(botonPlay);

	std::cout << "entering MenuState\n";
	return true;
}
bool MenuState::OnExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->ClearFromTextureMap("playButton");

	std::cout << "exiting MenuState\n";
	return true;
}