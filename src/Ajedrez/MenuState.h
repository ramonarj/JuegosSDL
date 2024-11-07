#ifndef __MENUSTATE__
#define __MENUSTATE__
#include "GameState.h"
#include "SDLGameObject.h"

class MenuState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;

	SDLGameObject* m_botonPlay;
};

#endif /* defined(__MenuState__) */