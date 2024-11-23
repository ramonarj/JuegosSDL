#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <string>
#include <vector>
#include "GameObject.h"

class Level;

/* Clase abstracta, igual que GameObject, para un estado de juego.
* 
Los estados que hereden solo deben implementar el método "OnEnter()", 
donde se crearán los Gameobjects y se añadirán al vector 'm_gameObjects */
class GameState
{
public:
	/* Destructora virtual */
	virtual ~GameState() {}

	/* Actualiza todos los GameObjects de la escena */
	void Update();
	/* Pinta todos los GameObjects de la escena */
	void Render();

	/* Función que debe implementarse para montar la escena */
	virtual bool OnEnter() = 0;
	/* Esta también puede sobreescribirse, pero si no se llama 
	explícitamente a la función padre, dejará basura */
	virtual bool OnExit();

	virtual std::string GetStateID() const = 0;

protected:
	GameState() : m_pLevel(nullptr) {}

	/* Lista de IDs de texturas */
	std::vector<std::string> m_textureIDList;

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;

	/* Carga un tilemap y todos los GameObjects que incluya */
	void LoadTilemapLevel(std::string tilemapName);

private:
	Level* m_pLevel;
};


#endif /* defined(__GameState__) */