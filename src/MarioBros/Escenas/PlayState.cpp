#include "PlayState.h"

#include "PauseState.h"
#include "GameOverState.h"

#include <iostream>

const std::string PlayState::s_playID = "PLAY";


bool PlayState::OnEnter()
{
	// Leer el nivel del TMX (método de GameState)
	LoadTilemapLevel("map2_largo.tmx");
	
	//LevelParser levelParser;
	//m_pLevel = levelParser.ParseLevel("map2_largo.tmx");

	// Colocar la cámara donde se quiera
	Camera::Instance()->SetPosition({ 320, 240 });

	// Música
	SoundManager::Instance()->Load("hit.wav", "hit", SOUND_SFX);
	SoundManager::Instance()->Load("Nivel 2.mp3", "nivel2", SOUND_MUSIC);

	SoundManager::Instance()->PlayMusic("nivel2", -1);

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::CheckCollision(GameObject* p1, GameObject* p2)
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