#ifndef __MENUSTATE__
#define __MENUSTATE__
#include "GameState.h"
#include "MenuButton.h"
#include <vector>

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

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__MenuState__) */