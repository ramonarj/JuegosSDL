#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "LoaderParams.h"

/* Clase abstracta y completamente genérica para un GameObject. Sirve tanto si usamos SDL
como si usamos cualquier otro motor/librería */
class GameObject
{
/* Los métodos son virtuales para poder usar el polimorfismo */
public:

	/* Inicializa el GameObject */
	virtual void Load(const LoaderParams* pParams) = 0;

	/* Dibuja el GameObject */
	virtual void Draw() = 0;
	/* Actualiza el GameObject */
	virtual void Update() = 0;
	/* Destruye y limpia el GameObject */
	virtual void Clean() = 0;


	//Nuevo
	inline bool IsActive() { return m_active; }
	inline void SetActive(bool active) { m_active = active; }

protected:
	GameObject() {}
	virtual ~GameObject() {}

	// Si está activo o no
	bool m_active;
};

#endif /* defined(__GameObject__) */
