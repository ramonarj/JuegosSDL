#include "GameState.h"

#include "TextureManager.h"
#include "LevelParser.h"
#include "ObjectLayer.h"
#include <iostream>

GameState::GameState() : m_pLevel(nullptr)
{
	// Cada estado tiene su propio gestor de colisiones
	m_pCollisionManager = new CollisionManager();
}

void GameState::Update()
{
	if(m_pLevel != nullptr)
	{
		m_pLevel->Update();
	}
	else
	{
		// Actualizar los GameObjects
		for (GameObject* o : m_gameObjects)
			o->Update();
	}

	// Colisiones
	m_pCollisionManager->Update();
}

void GameState::Render()
{
	if (m_pLevel != nullptr)
	{
		m_pLevel->Render();
	}
	else
	{
		// Pintar todos los GameObjects
		for (GameObject* o : m_gameObjects)
			o->Draw();
	}

	// Pintar colliders si es necesario
	m_pCollisionManager->Render();
}

bool GameState::OnExit()
{
	// si hay un nivel cargado, lo borramos (y los GameObjects los destruye él)
	if(m_pLevel != nullptr)
		delete m_pLevel;
	else
	{
		// clear gameobjects
		for (GameObject* o : m_gameObjects)
		{
			o->Clean();
			delete o;
			o = nullptr;
		}
		m_gameObjects.clear();
	}

	// clear the texture manager
	for (size_t i = 0; i < m_textureIDList.size(); i++)
	{
		TextureManager::Instance()->ClearFromTextureMap(m_textureIDList[i]);
	}

	// borrar el gestor de colisiones
	delete m_pCollisionManager;
	m_pCollisionManager = nullptr;

	std::cout << "\n* exiting " << GetStateID() << " state\n";
	return true;
}

void GameState::LoadTilemapLevel(std::string mapName)
{
	LevelParser levelParser;
	m_pLevel = levelParser.ParseLevel(mapName.c_str());

	// Actualizar la lista de GameObjects con los que hay en la ObjectLayer del nivel
	std::vector<Layer*>* layers = m_pLevel->GetLayers();
	for(Layer* l : *layers)
	{
		// Duck typing para encontrar las capas de objetos
		ObjectLayer* objLayer = dynamic_cast<ObjectLayer*>(l);
		if(objLayer != nullptr)
		{
			for (GameObject* go : *objLayer->GetGameObjects())
			{
				m_gameObjects.push_back(go);
			}
		}
	}
}