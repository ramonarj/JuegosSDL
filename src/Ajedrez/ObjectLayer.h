#ifndef __OBJECTLAYER__
#define __OBJECTLAYER__

#include "Layer.h"
#include "GameObject.h"
#include <vector>

/* Tipo de capa que solamente contiene GameObjects */
class ObjectLayer : public Layer
{
public:
	// Funciones b�sicas
	virtual void Update();
	virtual void Render();

	/* Devuelve un puntero a la lista de GameObjects */
	inline std::vector<GameObject*>* GetGameObjects() { return &m_gameObjects; }
private:
	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;
};


#endif /* defined(__TileLayer__) */