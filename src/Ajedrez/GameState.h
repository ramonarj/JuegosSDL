#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <string>
#include <vector>
#include "GameObject.h"

/* Clase abstracta, igual que GameObject, para un estado de juego */
class GameState
{
public:
	//aleluya
	virtual ~GameState() {}

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual bool OnEnter() = 0;
	virtual bool OnExit();

	virtual std::string GetStateID() const = 0;

protected:
	GameState() {}

	/* Lista de IDs de texturas */
	std::vector<std::string> m_textureIDList;

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;
};


#endif /* defined(__GameState__) */