#include "PlayState.h"

#include <iostream>
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Pieza.h"
#include "AnimatedGraphic.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::Update()
{
	// Con el escape, salimos al menú
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->GetStateMachine()->PushState(new PauseState());
	}

	// Actualizar los GameObjects
	for (GameObject* o : m_gameObjects)
		o->Update();

	// Comprobar colisiones entre la pieza y el fuego
	if (CheckCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), 
		dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
	{
		Game::Instance()->GetStateMachine()->PushState(new GameOverState());
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
	if (!TextureManager::Instance()->Load("Fuego.png", "fuego", Game::Instance()->GetRenderer()))
	{
		return false;
	}

	// Los LoaderParams habrá que borrarlos también no???
	GameObject* piezaViva = new Pieza();
	GameObject* fuego = new AnimatedGraphic();
	dynamic_cast<Pieza*>(piezaViva)->Load(new LoaderParams(320, 240, 46, 62, "piezas"));
	dynamic_cast<AnimatedGraphic*>(fuego)->Load(new LoaderParams(200, 200, 70, 95, "fuego", 4, 0, 6));
	m_gameObjects.push_back(piezaViva);
	m_gameObjects.push_back(fuego);

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

bool PlayState::CheckCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->GetPosition().GetX();
	rightA = p1->GetPosition().GetX() + p1->GetWidth();
	topA = p1->GetPosition().GetY();
	bottomA = p1->GetPosition().GetY() + p1->GetHeight();

	//Calculate the sides of rect B
	leftB = p2->GetPosition().GetX();
	rightB = p2->GetPosition().GetX() + p2->GetWidth();
	topB = p2->GetPosition().GetY();
	bottomB = p2->GetPosition().GetY() + p2->GetHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}