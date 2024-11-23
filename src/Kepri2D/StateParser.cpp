#include "StateParser.h"

#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

void StateParser::ParseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute); // push into list
		TextureManager::Instance()->Load(filenameAttribute, idAttribute, Game::Instance()->GetRenderer());
	}
}

void StateParser::ParseObjects(TiXmlElement* pStateRoot,
	std::vector<GameObject*>* pObjects)
{
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, frameWidth, frameHeight, numFrames, callbackID, animSpeed, fontSize;
		uint32_t textColor = 0;
		std::string textureID, text, font, colorStr;
		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("frameWidth", &frameWidth);
		e->Attribute("frameHeight", &frameHeight);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);
		e->QueryStringAttribute("textureID", &textureID);
		// Este método tiene una mejor detección de errores,
		// y no lanza excepción si no se encuentra el atributo
		e->QueryStringAttribute("text", &text);
		e->QueryStringAttribute("font", &font);
		e->Attribute("fontSize", &fontSize);
		e->QueryStringAttribute("textColor", &colorStr);
		if (colorStr != "") // leer el número que está en hexadecimal
		{ 
			std::stringstream ss;
			ss << std::hex << colorStr;
			ss >> textColor;
		}

		LoaderParams* pParams = new LoaderParams(x, y, width, height, frameWidth, frameHeight,
			textureID, numFrames, callbackID, animSpeed, text, font, fontSize, textColor);

		// Crear el GameObject y meterlo en la lista (lo que antes se hacía en el .cpp de los estados)
		GameObject* pGameObject = GameObjectFactory::Instance()->Create(e->Attribute("type"));
		pGameObject->Load(pParams);
		pObjects->push_back(pGameObject);

		// borrar el LoaderParams
		delete pParams;
	}
}

bool StateParser::ParseState(std::string stateFile, std::string stateID,
	std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs)
{
	// create the XML document
	TiXmlDocument xmlDoc;
	// load the state file
	if(!xmlDoc.LoadFile(STATES_PATH + stateFile))
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}

	// get the root element
	TiXmlElement* pRoot = xmlDoc.RootElement();
	// pre declare the states root node
	TiXmlElement* pStateRoot = 0;
	// get this states root node and assign it to pStateRoot
	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e =
		e->NextSiblingElement())
	{
		if (e->Value() == stateID)
		{
			pStateRoot = e;
		}
	}
	// pre declare the texture root
	TiXmlElement* pTextureRoot = 0;
	// get the root of the texture elements
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("TEXTURES"))
		{
			pTextureRoot = e;
		}
	}

	// now parse the textures
	ParseTextures(pTextureRoot, pTextureIDs);
	// pre declare the object root node
	TiXmlElement* pObjectRoot = 0;
	// get the root node and assign it to pObjectRoot
	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=
		NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("OBJECTS"))
		{
			pObjectRoot = e;
		}
	}
	// now parse the objects
	ParseObjects(pObjectRoot, pObjects);
	return true;
}