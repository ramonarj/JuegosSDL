#ifndef __MENUBUTTON__
#define __MENUBUTTON__
#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton(const LoaderParams* pParams, void (*callback)());

	// Heredadas
	virtual void Draw();
	virtual void Update();
	virtual void Clean();

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	/* Puntero a la función que se llamará al clicarlo */
	void (*m_callback)();

	/* Para el clic del ratón */
	bool m_bReleased;
};

#endif /* defined(__MenuButton__) */