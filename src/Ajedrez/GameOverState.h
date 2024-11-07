#ifndef __GAMEOVERSTATE__
#define __GAMEOVERSTATE__
#include "GameState.h"
#include "MenuButton.h"
#include <vector>

class GameOverState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return s_gameoverID; }

private:
	static const std::string s_gameoverID;

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;

	/* Callbacks para los botones (deben ser estáticas) */
	static void s_restartPlay();
	static void s_gameoverToMenu();
};

#endif /* defined(__GameOverState__) */