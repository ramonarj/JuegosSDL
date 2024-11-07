#ifndef __GAMESTATEMACHINE__
#define __GAMESTATEMACHINE__

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	/* Cambiar entre estados */
	void PushState(GameState* pState);
	void ChangeState(GameState* pState);
	void PopState();

	/* Funciones básicas */
	void Update();
	void Render();
private:
	std::vector<GameState*> m_gameStates;
};

#endif