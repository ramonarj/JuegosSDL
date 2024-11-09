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
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;
		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);
		textureID = e->Attribute("textureID");

		// Crear el GameObject y meterlo en la lista (lo que antes se hacía en el .cpp de los estados)
		GameObject* pGameObject = GameObjectFactory::Instance()->Create(e->Attribute("type"));
		pGameObject->Load(new LoaderParams
		(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
		pObjects->push_back(pGameObject);
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