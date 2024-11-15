#include "Level.h"

Level::~Level()
{
	// Borramos las capas
	for(Layer* l : m_layers)
	{
		delete l;
		l = nullptr;
	}
}

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