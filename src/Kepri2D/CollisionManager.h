#ifndef __COLLISIONMANAGER__
#define __COLLISIONMANAGER__

#include <vector>
#include "GameObject.h"

class TileLayer;

class CollisionManager
{
public:
	CollisionManager() : m_visibleColliders(false){}
	/* Comprueba las colisiones */
	void Update();

	void Render();

	/* Mete (true) o saca (false) del sistema de colisiones el GameObject dado */
	void SetCollidableObject(GameObject* g, bool collidable);

	/* Mete (true) o saca (false) del sistema de colisiones la capa de tiles dada */
	void SetCollidableLayer(TileLayer* g, bool collidable);

	/* Activa/desactiva el renderizado de los colliders */
	inline void VisibleColliders(bool visible) { m_visibleColliders = visible; }
private:
	/* Lista de GameObjects 'suscritos' al sistema de colisiones */
	std::vector<GameObject*> m_collidableObjects;

	/* Lista de capas de tiles con colisiones */
	std::vector<TileLayer*> m_collidableLayers;

	/* Si está a true, pintamos los colliders en el Render() */
	bool m_visibleColliders;

	// Funciones auxiliares para el Update()
	void ObjectObjectCollisions();
	void ObjectLayerCollisions();
};

#endif