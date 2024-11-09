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
#include "StateParser.h"

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
	// Lectura del estado actual del XML
	StateParser stateParser;
	stateParser.ParseState("play.xml", s_playID, &m_gameObjects, &m_textureIDList);


	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::OnExit()
{
	for (GameObject* o : m_gameObjects)
		o->Clean();

	m_gameObjects.clear();
	// clear the texture manager
	for (size_t i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "exiting PlayState\n";
	return true;
}

bool PlayState::CheckCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = (int)p1->GetPosition().GetX();
	rightA = (int)p1->GetPosition().GetX() + p1->GetWidth();
	topA = (int)p1->GetPosition().GetY();
	bottomA = (int)p1->GetPosition().GetY() + p1->GetHeight();

	//Calculate the sides of rect B
	leftB = (int)p2->GetPosition().GetX();
	rightB = (int)p2->GetPosition().GetX() + p2->GetWidth();
	topB = (int)p2->GetPosition().GetY();
	bottomB = (int)p2->GetPosition().GetY() + p2->GetHeight();

	//If any of the sides from A are outside of B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}