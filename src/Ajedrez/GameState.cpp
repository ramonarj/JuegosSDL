#include "GameState.h"

#include "TextureManager.h"
#include <iostream>

bool GameState::OnExit()
{
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

	std::cout << "* exiting " << GetStateID() << " state\n";
	return true;
}