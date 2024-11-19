#ifndef __STATEPARSER__
#define __STATEPARSER__

#include <iostream>
#include <vector>
#include "../../dependencies/tinyxml/tinyxml.h"

class GameObject;

static std::string STATES_PATH = "../../bin/assets/";

/* Se encarga de leer un archivo XML y rellenar las texturas y GameObjects de la escena */
class StateParser
{
public:
	/* Lee un estado de archivo */
	bool ParseState(std::string stateFile, std::string stateID, 
		std::vector<GameObject*>* pObjects, std::vector<std::string>* pTextureIDs);
private:
	/* Lee un GameObject de archivo */
	void ParseObjects(TiXmlElement* pStateRoot, std::vector<GameObject*>* pObjects);
	/* Lee una textura de archivo */
	void ParseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
};


#endif /* defined(__StateParser__) */
