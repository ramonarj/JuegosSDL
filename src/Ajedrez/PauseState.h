#ifndef __PAUSESTATE__
#define __PAUSESTATE__
#include "GameState.h"
#include "MenuButton.h"
#include <vector>

class PauseState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return s_PauseID; }

private:
	static const std::string s_PauseID;

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;

	/* Callbacks para los botones (deben ser estáticas) */
	static void s_resumePlay();
	static void s_pauseToMenu();
};

#endif /* defined(__PauseState__) */