#include "GameOverState.h"

#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include "PlayState.h"
#include "MenuState.h"
#include "InputHandler.h"

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
	GameObject* botonRestart = new MenuButton(new LoaderParams(200, 200, 200, 80, "restartButton"), s_restartPlay);
	GameObject* botonMenu = new MenuButton(new LoaderParams(200, 350, 200, 80, "menuButton"), s_gameoverToMenu);
	GameObject* gameoverImage = new SDLGameObject(new LoaderParams(200, 100, 190, 30, "gameover"));
	m_gameObjects.push_back(botonRestart);
	m_gameObjects.push_back(botonMenu);
	m_gameObjects.push_back(gameoverImage);

	std::cout << "entering entering GameOverState\n";
	return true;
}
bool GameOverState::OnExit()
{
	for (GameObject* o : m_gameObjects)
		o->Clean();

	m_gameObjects.clear();
	TextureManager::Instance()->ClearFromTextureMap("gameover");
	TextureManager::Instance()->ClearFromTextureMap("menuButton");
	TextureManager::Instance()->ClearFromTextureMap("restartButton");
	// reset the mouse button states to false
	InputHandler::Instance()->Reset();

	std::cout << "exiting GameOverState\n";
	return true;
}

void GameOverState::s_restartPlay()
{
	std::cout << "Restart" << std::endl;
	// Volver al PlayState
	Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

void GameOverState::s_gameoverToMenu()
{
	std::cout << "Go to menu" << std::endl;
	Game::Instance()->GetStateMachine()->ChangeState(new MenuState());
}