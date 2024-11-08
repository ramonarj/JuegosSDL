#ifndef __MENUBUTTON__
#define __MENUBUTTON__
#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton(){}
	void Load(const LoaderParams* pParams);

	// Heredadas
	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	/* Getter */
	int GetCallbackID() { return m_callbackID; }

	/* Establece la función a la que llamar */
	void SetCallback(void(*callback)()) { m_callback = callback; }

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	/* Puntero a la función que se llamará al clicarlo */
	void (*m_callback)();
	/* Identificador que le llega de archivo */
	int m_callbackID;

	/* Para el clic del ratón */
	bool m_bReleased;
};

#endif /* defined(__MenuButton__) */