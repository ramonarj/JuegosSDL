#ifndef __GAMEOBJECTFACTORY__
#define __GAMEOBJECTFACTORY__

#include <string>
#include <map>
#include <iostream>
#include "GameObject.h"

class BaseCreator
{
public:
	virtual GameObject* CreateGameObject() const = 0;
	virtual ~BaseCreator() {}
};

/* Clase singleton para crear GameObjects */
class GameObjectFactory
{
public:

	/* Devuelve la instancia */
	static GameObjectFactory* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new GameObjectFactory();
		return s_pInstance;
	}

	/* Registra un GameObject con un identificador y un creador dados */
	bool RegisterType(std::string typeID, BaseCreator* pCreator)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
		// if the type is already registered, do nothing
		if (it != m_creators.end())
		{
			delete pCreator;
			return false;
		}
		m_creators[typeID] = pCreator;
		return true;
	}

	/* Crea una instancia del GameObject previamente registrado y devuelve un puntero a él */
	GameObject* Create(std::string typeID)
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
		if (it == m_creators.end())
		{
			std::cout << "could not find type: " << typeID << "\n";
			return NULL;
		}
		BaseCreator* pCreator = (*it).second;
		return pCreator->CreateGameObject();
	}

	void Clean()
	{
		std::map<std::string, BaseCreator*>::iterator it = m_creators.begin();
		while(it != m_creators.end())
		{
			delete it->second;
			it++;
		}

		delete s_pInstance;
		s_pInstance = nullptr;
	}
private:
	GameObjectFactory(){}

	static GameObjectFactory* s_pInstance;

	/* Diccionario de creadores */
	std::map<std::string, BaseCreator*> m_creators;
};

#endif /* defined(__GameStateMachine__) */