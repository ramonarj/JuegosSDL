#include "PlayState.h"

#include <iostream>
#include "InputHandler.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"

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
	m_pLevel->Update();

	// Comprobar colisiones entre la pieza y el fuego
	if (CheckCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), 
		dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
	{
		Game::Instance()->GetStateMachine()->ChangeState(new GameOverState());
	}
}

void PlayState::Render()
{
	for (GameObject* o : m_gameObjects)
		o->Draw();
	m_pLevel->Render();
}

bool PlayState::OnEnter()
{
	// Lectura del estado actual del XML
	StateParser stateParser;
	stateParser.ParseState("play.xml", s_playID, &m_gameObjects, &m_textureIDList);

	// Leer el nivel y guardarlo en m_pLevel
	LevelParser levelParser;
	m_pLevel = levelParser.ParseLevel("map2.tmx");

	std::cout << "entering PlayState\n";
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