#ifndef __COLLISIONMANAGER__
#define __COLLISIONMANAGER__

#include <vector>
#include "GameObject.h"

class CollisionManager
{
public:
	CollisionManager() : m_visibleColliders(false){}
	/* Comprueba las colisiones */
	void Update();

	void Render();

	/* Mete (true) o saca (false) del sistema de colisiones el GameObject dado */
	void SetCollidableObject(GameObject* g, bool collidable);

	/* Activa/desactiva el renderizado de los colliders */
	inline void VisibleColliders(bool visible) { m_visibleColliders = visible; }
private:
	/* Lista de GameObjects 'suscritos' al sistema de colisiones */
	std::vector<GameObject*> m_collidableObjects;

	/* Si está a true, pintamos los colliders en el Render() */
	bool m_visibleColliders;
};

#endif