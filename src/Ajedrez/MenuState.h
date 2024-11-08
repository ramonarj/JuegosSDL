#ifndef __MENUSTATE__
#define __MENUSTATE__
#include "GameState.h"
#include "MenuButton.h"
#include <vector>

/* Clase abstracta para estados que tengan botones con callbacks */
class MenuState : public GameState
{
protected:
	typedef void(*Callback)();

	/* Función que asigna a cada botón su callback */
	virtual void SetCallbacks(const std::vector<Callback>& callbacks)= 0;

	/* Vector de callbacks */
	std::vector<Callback> m_callbacks;
};

#endif /* defined(__MenuState__) */