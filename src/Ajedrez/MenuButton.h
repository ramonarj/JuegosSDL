#ifndef __MENUBUTTON__
#define __MENUBUTTON__
#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
public:
	MenuButton(const LoaderParams* pParams);

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
};

#endif /* defined(__MenuButton__) */