#include "PlayState.h"

#include <iostream>
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "MenuState.h"
#include "Pieza.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::Update()
{
	for (GameObject* o : m_gameObjects)
		o->Update();

	// Con el escape, salimos al menú
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->GetStateMachine()->PopState();
	}
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
	GameObject* piezaViva = new Pieza(new LoaderParams(350, 350, 46, 62, "piezas"));
	m_gameObjects.push_back(piezaViva);

	return true;
}

bool PlayState::OnExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Clean();
	}
	m_gameObjects.clear();
	TextureManager::Instance()->ClearFromTextureMap("piezas");

	std::cout << "exiting PlayState\n";
	return true;
}