#ifndef __MAINMENUSTATE__
#define __MAINMENUSTATE__

#include "MenuState.h"

class MainMenuState : public MenuState
{
public:
	// Los hereda de GameState
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	// Lo hereda de MenuState
	virtual void SetCallbacks(const std::vector<Callback>& callbacks);

	virtual std::string GetStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;
	/* Lista de IDs de texturas */
	std::vector<std::string> m_textureIDList;

	/* Callbacks para los botones (deben ser estáticas) */
	static void s_menuToPlay();
	static void s_exitFromMenu();
};

#endif /* defined(__GameOverState__) */