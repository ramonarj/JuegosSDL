#ifndef __GAMEOVERSTATE__
#define __GAMEOVERSTATE__

#include "Kepri2D.h"

class GameOverState : public MenuState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();

	// Lo hereda de MenuState
	virtual void SetCallbacks(const std::vector<Callback>& callbacks);

	virtual std::string GetStateID() const { return s_gameoverID; }

private:
	static const std::string s_gameoverID;

	/* Callbacks para los botones (deben ser estáticas) */
	static void s_restartPlay();
	static void s_gameoverToMenu();
};

#endif /* defined(__GameOverState__) */