#include "TileLayer.h"

#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include "InputHandler.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets) :
	m_tileSize(tileSize), m_tilesets(tilesets), m_position(0, 0), m_velocity(0, 0)
{
	// Obviamente, el tamaño de la ventana (tanto anchura como altura) 
	// debe ser múltiplo del tamaño de tile que decidamos, para que 
	// estas divisiones den unas filas y columnas exactas
	m_numColumns = (Game::Instance()->GetGameWidth() / m_tileSize);
	m_numRows = (Game::Instance()->GetGameHeight() / m_tileSize);
}

void TileLayer::Update()
{
	m_velocity = Vector2D(0, 0);
	// prueba para el scroll
	if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
		m_velocity += Vector2D(2, 0);
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
		m_velocity += Vector2D(-2, 0);
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
		m_velocity += Vector2D(0, -2);
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
		m_velocity += Vector2D(0, 2);
	// actualizar la posición
	m_position += m_velocity;
}

void TileLayer::Render()
{
	// Las coordenadas (en la matriz de IDs) del primer tile
	// que se va a pintar en la esquina superior izquierda de la pantalla
	int x = int(m_position.GetX() / m_tileSize);
	int y = int(m_position.GetY() / m_tileSize);

	// Desplazamiento (px) hacia la izquierda/arriba de ese tile
	// Cuanto mayor sean, menos tile se verá. 0 <= (x2, y2) <= m_tileSize
	int x2 = int(m_position.GetX()) % m_tileSize;
	int y2 = int(m_position.GetY()) % m_tileSize;

	// Recorremos los tiles visibles y los pintamos
	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			int id = m_tileIDs[i + y][j + x]; //%numRows, %numColumns para hacer toroide
			// tile vacío; pasamos al siguiente
			if (id == 0)
			{
				continue;
			}
			// cogemos el tileset que contiene este tile
			Tileset tileset = GetTilesetByID(id);
			id--;
			// Dibujamos el tile con los parámetros necesarios
			TextureManager::Instance()->DrawTile(tileset.name, tileset.margin, tileset.spacing,
				(j * m_tileSize) - x2, (i * m_tileSize) - y2, //posición
				m_tileSize, m_tileSize, //dimensiones
				(id - (tileset.firstGridID - 1)) / tileset.numColumns, //fila
				(id - (tileset.firstGridID - 1)) % tileset.numColumns, //columna
				Game::Instance()->GetRenderer());
		}
	}
}

Tileset TileLayer::GetTilesetByID(int tileID)
{
	// recorremos los tilesets para buscar el que corresponde al tile dado
	for (size_t i = 0; i < m_tilesets.size(); i++)
	{
		// para comprobar que no es el último de la lista
		if (i + 1 <= m_tilesets.size() - 1)
		{
			// si el firstgid(tilesetActual) <= tileID < firstgid(tilesetSiguiente), 
			// es que el tile pertenece al tileset actual
			if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i + 1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		// si solo queda uno por comprobar, se devuelve ese
		else
		{
			return m_tilesets[i];
		}
	}
	std::cout << "did not find tileset, returning empty tileset\n";
	Tileset t;
	return t;
}