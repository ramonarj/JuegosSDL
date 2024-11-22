#ifndef __TILELAYER__
#define __TILELAYER__

#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"

/* Tipo de capa que solamente contiene tiles */
class TileLayer : public Layer
{
public:
	/* Constructora */
	TileLayer(int tileSize, int mapWidth, int mapHeight, 
		const std::vector<Tileset>& tilesets, Vector2D parallax = {1,1});

	virtual ~TileLayer(){}

	// Funciones b�sicas
	virtual void Update();
	virtual void Render();

	// Setters
	/* Rellena la capa con la informaci�n de tiles dada */
	inline void SetTileIDs(const std::vector<std::vector<int>>& data) { m_tileIDs = data; }
	inline void SetTileSize(int tileSize) { m_tileSize = tileSize; }

	// Getters
	/* Devuelve el tileset concreto que contiene el tile con el ID dado */
	inline Tileset GetTilesetByID(int tileID);

private:
	/* Dimensiones de la capa */
	int m_numColumns;
	int m_numRows;
	/* Tama�o de cada tile (son cuadrados) */
	int m_tileSize;
	/* Tama�o completo (en n�mero de tiles) del mapa */
	int m_mapWidth;
	int m_mapHeight;
	/* �ndice de paralaje en ambos ejes. Cuanto m�s grande, m�s cerca del espectador.
	El predeterminado es (1, 1) */
	Vector2D m_parallax;

	/* Posici�n y velocidad actuales de la capa */
	Vector2D m_position;
	Vector2D m_velocity;

	/* Referencia a los tilesets usados en esta capa */
	const std::vector<Tileset>& m_tilesets;

	/* Matriz de identificadores de tiles */
	std::vector<std::vector<int>> m_tileIDs;
};

#endif /* defined(__TileLayer__) */