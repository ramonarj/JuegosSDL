#include "TileLayer.h"

#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include "InputHandler.h"
#include "Camera.h"

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset>& tilesets, Vector2D parallax) :
	m_tileSize(tileSize), m_mapWidth(mapWidth), m_mapHeight(mapHeight), m_tilesets(tilesets), 
	m_parallax(parallax), m_position(0, 0), m_velocity(0, 0)
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

	// esto es solamente una prueba para mover distintas capas por separado
	// (efecto de viento / tormenta / nubes moviéndose)
	if (m_parallax.GetX() <= 0.55f)
		m_position += Vector2D(-3, 0);
	// actualizar la posición según la velocidad y la profundidad
	// a la que se encuentre la capa (paralaje)
	m_position += m_velocity * (Vector2D(1, 1) - m_parallax);

	// La cámara se moverá con la velocidad que le hemos pasado
	if(m_parallax.GetX() == 1)
	{
		//Camera::Instance()->Update();
	}
}

void TileLayer::Render()
{
	Vector2D cameraPos = Camera::Instance()->GetPosition();
	int windowWidth = Game::Instance()->GetGameWidth();
	int windowHeight = Game::Instance()->GetGameHeight();
	
	// Las coordenadas (en la matriz de IDs) del primer tile
	// que se va a pintar en la esquina superior izquierda de la pantalla
	int x = int((cameraPos.GetX() - (windowWidth / 2) - m_position.GetX()) / m_tileSize);
	int y = int((cameraPos.GetY() - (windowHeight / 2) - m_position.GetY()) / m_tileSize);

	// Desplazamiento (px) hacia la izquierda/arriba de ese tile
	// Cuanto mayor sean, menos tile se verá. 0 <= (x2, y2) <= m_tileSize
	int x2 = int(cameraPos.GetX() - (windowWidth / 2) - m_position.GetX()) % m_tileSize;
	int y2 = int(cameraPos.GetY() - (windowHeight / 2) - m_position.GetY()) % m_tileSize;

	// Recorremos los tiles visibles y los pintamos
	// Los '+1' son para que no se vean cortados los tiles que van saliendo al hacer scroll
	for (int i = 0; i < m_numRows + 1; i++)
	{
		for (int j = 0; j < m_numColumns + 1; j++)
		{
			// tile fuera del mapa; siguiente
			if (i + y < 0 || x + j < 0)
				continue;
			int id = m_tileIDs[(i + y) % m_mapHeight][(j + x) % m_mapWidth]; // % para hacer toroide
			// tile vacío; pasamos al siguiente
			if (id == 0)
			{
				continue;
			}


			// cogemos el tileset que contiene este tile
			Tileset tileset = GetTilesetByID(id);
			id--;

			// draw the tile into position while offsetting its x
			//position bysubtracting the camera position
			TextureManager::Instance()->DrawTile(tileset.name, tileset.margin, tileset.spacing, 
				((j * m_tileSize) - x2), ((i * m_tileSize) - y2), // posición
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