#include "Level.h"

void Level::Update()
{
	// Actualizar todas las capas
	for(Layer* l : m_layers)
	{
		l->Update();
	}
}

void Level::Render()
{
	// Pintar todas las capas
	for (Layer* l : m_layers)
	{
		l->Render();
	}
}