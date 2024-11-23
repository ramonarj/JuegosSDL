#ifndef __MAINMENUSTATE__
#define __MAINMENUSTATE__

#include "Kepri2D.h"

class MainMenuState : public MenuState
{
public:
	MainMenuState(){}

	// Hereda de GameState
	virtual bool OnEnter();

	// Lo hereda de MenuState
	virtual void SetCallbacks(const std::vector<Callback>& callbacks);

	virtual std::string GetStateID() const { return s_menuID; }

private:
	static const std::string s_menuID;

	/* Callbacks para los botones (deben ser estáticas) */
	static void s_menuToPlay();
	static void s_exitFromMenu();
};

#endif /* defined(__MainMenuState__) */