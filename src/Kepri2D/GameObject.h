#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "LoaderParams.h"

/* Clase abstracta y completamente genérica para un GameObject. Sirve tanto si usamos SDL
como si usamos cualquier otro motor/librería */
class GameObject
{
/* Los métodos son virtuales para poder usar el polimorfismo */
public:

	virtual ~GameObject(){}

	/* Inicializa el GameObject */
	virtual void Load(const LoaderParams* pParams) = 0;

	/* Dibuja el GameObject */
	virtual void Draw() = 0;
	/* Actualiza el GameObject */
	virtual void Update() = 0;
	/* Destruye y limpia el GameObject */
	virtual void Clean() = 0;

protected:
	GameObject() {}
};

#endif /* defined(__GameObject__) */
