#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "LoaderParams.h"

/* Clase abstracta y completamente genérica para un GameObject. Sirve tanto si usamos SDL
como si usamos cualquier otro motor/librería */
class GameObject
{
/* Los métodos son virtuales para poder usar el polimorfismo */
public:

	/* Dibuja el GameObject */
	virtual void Draw() = 0;
	/* Actualiza el GameObject */
	virtual void Update() = 0;
	/* Destruye y limpia el GameObject */
	virtual void Clean() = 0;

protected:
	/* Constructora con los parámetros de carga */
	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}
};

#endif /* defined(__GameObject__) */
