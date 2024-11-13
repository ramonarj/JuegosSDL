#ifndef __LEVEL__
#define __LEVEL__

#include <string>
#include <vector>
#include "Layer.h"

/* Representaci�n de un tileset, con la informaci�n del .tmx */
struct Tileset
{
	// Primer tileID que cocresponde a este tileset
	int firstGridID;

	// Dimensiones de cada tile en p�xeles
	int tileWidth;
	int tileHeight;

	// Espaciado entre tiles y margen con el borde
	int spacing;
	int margin;

	// Dimensiones del tileset en p�xeles
	int width;
	int height;

	// N�mero de columnas que contiene el tileset
	int numColumns;

	/* Nombre de la textura que usa el tileset */
	std::string name;
};

/* Se encarga de dibujar y actualizar las capas, y contiene la colecci�n de tilesets del nivel */
class Level
{
public:
	~Level() {}

	// M�todos b�sicos
	void Update();
	void Render();

	// Getters
	/* Devuelve un puntero a la colecci�n de Tilesets usados en el nivel */
	inline std::vector<Tileset>* GetTilesets() { return &m_tilesets; }
	/* Devuelve un puntero a la colecci�n de capas del nivel */
	inline std::vector<Layer*>* GetLayers() { return &m_layers; }

private:
	// Para asegurarnos de que solamente el LevelParser pueda
	// crear una instancia de 'Level'
	friend class LevelParser;
	Level(){}

	/* Tilesets del nivel */
	std::vector<Tileset> m_tilesets;
	/* Lista de capas del nivel */
	std::vector<Layer*> m_layers;
};

#endif /* defined(__Level__) */