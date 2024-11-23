#include "GameState.h"

#include "TextureManager.h"
#include "LevelParser.h"
#include <iostream>

void GameState::Update()
{
	if(m_pLevel != nullptr)
	{
		m_pLevel->Update();
		return;
	}
	// Actualizar los GameObjects
	for (GameObject* o : m_gameObjects)
		o->Update();
}

void GameState::Render()
{
	if (m_pLevel != nullptr)
	{
		m_pLevel->Render();
		return;
	}
	// Pintar todos los GameObjects
	for (GameObject* o : m_gameObjects)
		o->Draw();
}

bool GameState::OnExit()
{
	// si hay un nivel cargado, lo borramos
	if(m_pLevel != nullptr)
		delete m_pLevel;

	// clear gameobjects
	for (GameObject* o : m_gameObjects)
	{
		o->Clean();
		delete o;
		o = nullptr;
	}
	m_gameObjects.clear();

	// clear the texture manager
	for (size_t i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
	}

	std::cout << "\n* exiting " << GetStateID() << " state\n";
	return true;
}

void GameState::LoadTilemapLevel(std::string mapName)
{
	LevelParser levelParser;
	m_pLevel = levelParser.ParseLevel(mapName.c_str());
}