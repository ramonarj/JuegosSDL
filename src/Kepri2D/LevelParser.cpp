#include "LevelParser.h"

#include "TileLayer.h"
#include "ObjectLayer.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObjectFactory.h"

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

	// 1) parse the tilesets
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			// rellena los tilesets del nivel construido
			ParseTilesets(e, pLevel->GetTilesets());
		}
	}


	// 2) parse any textures (from <properties>)
	TiXmlElement* pProperties = pRoot->FirstChildElement();
	for (TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("property"))
		{
			ParseTexture(e);
		}
	}


	// 3) parse any layers
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
		{
			// Capa de objetos
			if (e->FirstChildElement()->Value() == std::string("object"))
			{
				ParseObjectLayer(e, pLevel->GetLayers());
			}
			// Capa de tiles
			else if (e->FirstChildElement()->Value() == std::string("data"))
			{
				ParseTileLayer(e, pLevel->GetLayers(), pLevel->GetTilesets());
			}
		}
	}
	// devolver el nivel ya leído
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
	// Creamos una nueva capa con los tilesets ya obtenidos y con las características
	// que se indiquen (dimensiones totales e índice de paralaje)
	int mapWidth, mapHeight;
	pTileElement->Attribute("width", &mapWidth);
	pTileElement->Attribute("height", &mapHeight);
	// más complicado porque es float, y no int
	Vector2D parallax = { 1,1 };
	const char* parallaxxStr = pTileElement->Attribute("parallaxx");
	if (parallaxxStr != NULL)
		parallax.SetX(std::stof(parallaxxStr)); //string to float
	TileLayer* pTileLayer = new TileLayer(m_tileSize, mapWidth, mapHeight, *pTilesets, parallax);


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

void LevelParser::ParseTexture(TiXmlElement* pTextureRoot)
{
	// ruta de la imagen desde el archivo .tmx (images/~~~.png)
	std::string imageRoute = pTextureRoot->Attribute("value");
	// Carga la textura usando el atributo "name" para el ID
	TextureManager::Instance()->Load(TILEMAPS_PATH + imageRoute, pTextureRoot->Attribute("name"),
		Game::Instance()->GetRenderer(), true);
}

void LevelParser::ParseObjectLayer(TiXmlElement* pObjectElement, std::vector<Layer*>* pLayers)
{
	// create an object layer
	ObjectLayer* pObjectLayer = new ObjectLayer();

	// Iteramos todos los objetos de la capa
	for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::cout << e->Value();
		if (e->Value() == std::string("object"))
		{
			// Parámetros para LoaderParams con sus valores por defecto
			int x, y, width, height, numFrames, animSpeed, callbackID;
			x = y = width = height = callbackID = 0;
			numFrames = animSpeed = 1;
			std::string textureID;

			// La X e Y la cogemos directamente del nodo del objeto
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			GameObject* pGameObject = GameObjectFactory::Instance()->Create(e -> Attribute("type"));

			// Buscamos el nodo "propierties"
			for (TiXmlElement* properties = e->FirstChildElement(); properties != NULL; 
				properties = properties -> NextSiblingElement())
			{
				if (properties->Value() == std::string("properties"))
				{
					// Iteramos todas las propiedades del objeto
					for (TiXmlElement* property = properties -> FirstChildElement(); property != NULL; 
						property = property -> NextSiblingElement())
					{
						if (property->Value() == std::string("property"))
						{
							// Por desgracia, C++ no soporta el tipo <string> en la
							// instrucción 'switch', así que hay que hacer este if-else kilométrico
							if (property->Attribute("name") == std::string("numFrames"))
							{
								property->Attribute("value", &numFrames);
							}
							else if (property->Attribute("name") == std::string("textureHeight"))
							{
								property->Attribute("value", &height);
							}
							else if (property->Attribute("name") == std::string("textureID"))
							{
								textureID = property->Attribute("value");
							}
							else if (property->Attribute("name") == std::string("textureWidth"))
							{
								property->Attribute("value", &width);
							}
							else if (property->Attribute("name") == std::string("callbackID"))
							{
								property->Attribute("value", &callbackID);
							}
							else if (property->Attribute("name") == std::string("animSpeed"))
							{
								property->Attribute("value", &animSpeed);
							}
						}
					}
				}
			}
			// Inicializamos el GameObject y lo añadimos a la lista
			LoaderParams* pParams = new LoaderParams(x, y, width, height, textureID,
				numFrames, callbackID, animSpeed);
			pGameObject->Load(pParams);
			pObjectLayer->GetGameObjects()->push_back(pGameObject);

			//importante
			delete pParams;
		}
	}
	// Metemos la capa de objetos creada
	pLayers->push_back(pObjectLayer);
}