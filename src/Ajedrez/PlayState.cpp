#include "PlayState.h"

#include <iostream>
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Pieza.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::Update()
{
	// Con el escape, salimos al menú
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->GetStateMachine()->PushState(new PauseState());
	}

	for (GameObject* o : m_gameObjects)
		o->Update();
}

void PlayState::Render()
{
	for (GameObject* o : m_gameObjects)
		o->Draw();
}

bool PlayState::OnEnter()
{
	std::cout << "entering PlayState\n";

	// Carga de recursos con TextureManager
	if (!TextureManager::Instance()->Load("Piezas.png", "piezas", Game::Instance()->GetRenderer()))
	{
		return false;
	}

	// Los LoaderParams habrá que borrarlos también no???
	GameObject* piezaViva = new Pieza(new LoaderParams(320, 240, 46, 62, "piezas"));
	m_gameObjects.push_back(piezaViva);

	return true;
}

bool PlayState::OnExit()
{
	for (GameObject* o : m_gameObjects)
		o->Clean();

	m_gameObjects.clear();
	TextureManager::Instance()->ClearFromTextureMap("piezas");

	std::cout << "exiting PlayState\n";
	return true;
}