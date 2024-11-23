#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <string>
#include <vector>
#include "GameObject.h"
#include "CollisionManager.h"

class Level;

/* Clase abstracta, igual que GameObject, para un estado de juego.
* 
Los estados que hereden solo deben implementar el m�todo "OnEnter()", 
donde se crear�n los Gameobjects y se a�adir�n al vector 'm_gameObjects */
class GameState
{
public:
	/* Destructora virtual */
	virtual ~GameState() {}

	/* Actualiza todos los GameObjects de la escena */
	void Update();
	/* Pinta todos los GameObjects de la escena */
	void Render();

	/* Funci�n que debe implementarse para montar la escena */
	virtual bool OnEnter() = 0;
	/* Esta tambi�n puede sobreescribirse, pero si no se llama 
	expl�citamente a la funci�n padre, dejar� basura */
	virtual bool OnExit();

	virtual std::string GetStateID() const = 0;

protected:
	/* Constructora por defecto*/
	GameState();

	/* Lista de IDs de texturas. Esto ahora mismo parece que no se usa para nada */
	std::vector<std::string> m_textureIDList;

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;

	/* Gestor de colisiones del estado actual */
	CollisionManager* m_pCollisionManager;

	/* Carga un tilemap y todos los GameObjects que incluya */
	void LoadTilemapLevel(std::string tilemapName);

private:
	Level* m_pLevel;
};


#endif /* defined(__GameState__) */