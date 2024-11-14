#include "ObjectLayer.h"

void ObjectLayer::Update()
{
	// Actualizar los GameObjects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update();
	}
}
void ObjectLayer::Render()
{
	// Pintar los GameObjects
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Draw();
	}
}