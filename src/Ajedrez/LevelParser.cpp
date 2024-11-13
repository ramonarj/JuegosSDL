#include "LevelParser.h"

#include "TileLayer.h"
#include "Game.h"
#include "TextureManager.h"

// Las 2 librerías necesarias para decodificar los tilemaps
#include "base64.h"
#include "zlib.h"

Level* LevelParser::ParseLevel(const char* levelFile)
{
	// create a TinyXML document and load the map XML
	TiXmlDocument levelDocument;
	levelDocument.LoadFile(TILEMAPS_PATH + levelFile);

	// create the level object
	Level* pLevel = new Level();

	// get the root node
	TiXmlElement* pRoot = levelDocument.RootElement();
	pRoot->Attribute("tilewidth", &m_tileSize);
	pRoot->Attribute("width", &m_width);
	pRoot->Attribute("height", &m_height);

	// parse the tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			// rellena los tilesets del nivel construido
			ParseTilesets(e, pLevel->GetTilesets());
		}
	}

	// parse any object layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			// rellena las capas del nivel construido
			ParseTileLayer(e, pLevel->GetLayers(), pLevel->GetTilesets());
		}
	}
	return pLevel;
}

void LevelParser::ParseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
	// ruta de la imagen desde el archivo .tmx (images/~~~.png)
	std::string imageRoute = pTilesetRoot->FirstChildElement()->Attribute("source");
	// Añadimos la textura del tileset al TextureManager, con el nombre especificado en el .tmx
	TextureManager::Instance()->Load(TILEMAPS_PATH + imageRoute,  pTilesetRoot -> Attribute("name"), 
		Game::Instance()->GetRenderer(), true);

	// Creamos un objeto tileset y lo rellenamos con los datos del documento
	Tileset tileset;
	pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);
	pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height);
	pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
	pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
	pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
	pTilesetRoot->Attribute("spacing", &tileset.spacing);
	pTilesetRoot->Attribute("margin", &tileset.margin);
	tileset.name = pTilesetRoot->Attribute("name");
	tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

	// Lo añadimos a la lista de tilesets
	pTilesets->push_back(tileset);
}

void LevelParser::ParseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, 
	const std::vector<Tileset>* pTilesets)
{
	// Creamos una nueva capa con los tilesets ya obtenidos
	TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets);
	// tile data
	std::vector<std::vector<int>> data;
	std::string decodedIDs;
	TiXmlElement* pDataNode = nullptr;

	// llegamos a los datos
	for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
	}
	// decodificar la información en base 64
	for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
	{
		TiXmlText* text = e->ToText();
		std::string t = text->Value();
		decodedIDs = base64_decode(t);
	}

	// descomprimir el formato zlib y meter la info en el vector 'ids'
	uLongf sizeofids = m_width * m_height * sizeof(int);
	std::vector<int> ids(m_width * m_height);
	uncompress((Bytef*)&ids[0], &sizeofids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

	// añadir filas a la matriz...
	std::vector<int> layerRow(m_width);
	for (int j = 0; j < m_height; j++)
	{
		data.push_back(layerRow);
	}
	// ... y rellenarla con los datos ya decodificados y descomprimidos en 'ids'
	for (int rows = 0; rows < m_height; rows++)
	{
		for (int cols = 0; cols < m_width; cols++)
		{
			data[rows][cols] = ids[rows * m_width + cols];
		}
	}

	// Terminar de crear la capa y añadirla a la lista de capas del nivel
	pTileLayer->SetTileIDs(data);
	pLayers->push_back(pTileLayer);
}