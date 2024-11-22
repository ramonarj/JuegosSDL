#ifndef __LEVELPARSER__
#define __LEVELPARSER__

#include "Level.h"
#include "../../dependencies/tinyxml/tinyxml.h"

const std::string TILEMAPS_PATH = "../../bin/assets/tilemaps/";

/* Clase encargada de crear los niveles a partir de un archivo XML de Tiled (.tmx) */
class LevelParser
{
public:
	/* Crea un nivel a partir de un archivo de Tiled (.tmx) dado */
	Level* ParseLevel(const char* levelFile);
private:
	int m_tileSize;
	int m_width;
	int m_height;

	// Para las capas de tiles
	void ParseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void ParseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, 
		const std::vector<Tileset>* pTilesets, std::vector<Layer*>* pCollisionLayers);

	// Para las capas de objetos
	void ParseTexture(TiXmlElement* pTextureRoot);
	void ParseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers);
};

#endif