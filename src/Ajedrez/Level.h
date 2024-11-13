#ifndef __LEVEL__
#define __LEVEL__

#include <string>
#include <vector>
#include "Layer.h"

/* Representación de un tileset, con la información del .tmx */
struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

/* Se encarga de dibujar y actualizar las capas, y contiene la colección de tilesets del nivel */
class Level
{
public:
	Level();
	~Level() {}

	// Métodos básicos
	void Update();
	void Render();

	// Getters
	/* Devuelve un puntero a la colección de Tilesets usados en el nivel */
	inline std::vector<Tileset>* GetTilesets() { return &m_tilesets; }
	/* Devuelve un puntero a la colección de capas del nivel */
	inline std::vector<Layer*>* GetLayers() { return &m_layers; }

private:
	/* Tilesets del nivel */
	std::vector<Tileset> m_tilesets;
	/* Lista de capas del nivel */
	std::vector<Layer*> m_layers;
};

#endif /* defined(__Level__) */