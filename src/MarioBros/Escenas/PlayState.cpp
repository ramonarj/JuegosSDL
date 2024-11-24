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
	Camera::Instance()->SetBackgroundColor(0x5077d2ff);
	Camera::Instance()->SetTarget(&m_gameObjects[0]->GetPosition());

	// Música
	SoundManager::Instance()->Load("hit.wav", "hit", SOUND_SFX);
	SoundManager::Instance()->Load("Nivel 2.mp3", "nivel2", SOUND_MUSIC);

	SoundManager::Instance()->PlayMusic("nivel2", -1);

	// Iniciar colisiones entre la pieza y el fuego
	m_pCollisionManager->SetCollidableObject(m_gameObjects[0], true);
	m_pCollisionManager->SetCollidableObject(m_gameObjects[1], true);
	m_pCollisionManager->VisibleColliders(true);

	std::cout << "entering PlayState\n";
	return true;
}