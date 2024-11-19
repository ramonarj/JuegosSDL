#include "ObjectLayer.h"

ObjectLayer::~ObjectLayer()
{
	// Borrar todos los objetos leídos del mapa
	for(GameObject* go : m_gameObjects)
	{
		delete go;
		go = nullptr;
	}
	m_gameObjects.clear();
}

void ObjectLayer::Update()
{
	// Actualizar los GameObjects
	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update();
	}
}
void ObjectLayer::Render()
{
	// Pintar los GameObjects
	for (size_t i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Draw();
	}
}