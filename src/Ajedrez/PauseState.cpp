#include "PauseState.h"

#include "TextureManager.h"
#include "Game.h"
#include <iostream>
#include "PlayState.h"
#include "MenuState.h"
#include "InputHandler.h"

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
	// Carga las texturas necesarias para este estado
	if (!TextureManager::Instance()->Load("ResumeButton.png", "resumeButton", Game::Instance()->GetRenderer()))
	{
		return false;
	}
	if (!TextureManager::Instance()->Load("MenuButton.png", "menuButton", Game::Instance()->GetRenderer()))
	{
		return false;
	}
	
	// Crea los GameObjects y los añade a la lista
	GameObject* botonResume = new MenuButton(new LoaderParams(200, 200, 200, 80, "resumeButton"), s_resumePlay);
	GameObject* botonMenu = new MenuButton(new LoaderParams(200, 350, 200, 80, "menuButton"), s_pauseToMenu);
	m_gameObjects.push_back(botonResume);
	m_gameObjects.push_back(botonMenu);

	std::cout << "entering PauseState\n";
	return true;
}
bool PauseState::OnExit()
{
	for (GameObject* o : m_gameObjects)
		o->Clean();

	m_gameObjects.clear();
	TextureManager::Instance()->ClearFromTextureMap("menuButton");
	TextureManager::Instance()->ClearFromTextureMap("resumeButton");
	// reset the mouse button states to false
	InputHandler::Instance()->Reset();

	std::cout << "exiting PauseState\n";
	return true;
}

void PauseState::s_resumePlay()
{
	// Volver al PlayState
	Game::Instance()->GetStateMachine()->PopState();
}

void PauseState::s_pauseToMenu()
{
	Game::Instance()->GetStateMachine()->ChangeState(new MenuState());
}