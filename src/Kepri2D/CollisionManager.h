#ifndef __COLLISIONMANAGER__
#define __COLLISIONMANAGER__

#include <vector>
#include "GameObject.h"

class CollisionManager
{
public:
	/* Comprueba las colisiones */
	void Update();

	/* Mete (true) o saca (false) del sistema de colisiones el GameObject dado */
	void SetCollidableObject(GameObject* g, bool collidable);
private:
	/* Lista de GameObjects 'suscritos' al sistema de colisiones */
	std::vector<GameObject*> m_collidableObjects;
};

#endif