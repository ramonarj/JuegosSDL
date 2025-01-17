#ifndef __GAMESTATEMACHINE__
#define __GAMESTATEMACHINE__

#include "GameState.h"
#include <vector>
#include "checkML.h"

/* Clase singleton que gestiona los estados de juego (como un SceneManager) */
class GameStateMachine
{
public:
	/* Devuelve la instancia */
	static GameStateMachine* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new GameStateMachine();
		return s_pInstance;
	}

	/* A�ade un estado encima del actual, sin eliminarlo */
	void PushState(GameState* pState);
	/* Cambia al estado dado despu�s de acabar el Update(), y elimina el actual */
	void ChangeState(GameState* pState);
	/* Elimina el estado m�s reciente */
	void PopState();

	/* Funciones b�sicas */
	void Update();
	void Render();

	inline void Clean()
	{
		while(!m_gameStates.empty())
			Pop();
		delete s_pInstance;
		s_pInstance = nullptr;
	}
private:
	enum transition_type
	{
		NONE = 0,
		PUSH = 1,
		POP = 2,
		CHANGE = 3
	};

	/* Instancia */
	static GameStateMachine* s_pInstance;

	/* Constructora por defecto */
	GameStateMachine() : m_transitionType(NONE), m_nextState(nullptr) {}

	/* Estados de juego */
	std::vector<GameState*> m_gameStates;

	/* Tipo de transici�n que nos piden */
	transition_type m_transitionType;

	/* Nuevo estado que nos piden meter, pero hay que esperar 
	a que termine el 'Update()' del actual para hacerlo. No aplicable a pop() */
	GameState* m_nextState;

	// M�todo privado que cambia de verdad el estado
	void ChangeStatePrivate();

	/* M�todos privados para mayor comodidad */
	inline void Pop()
	{
		m_gameStates.back()->OnExit();
		delete m_gameStates.back();
		m_gameStates.pop_back();
	}
	inline void Push()
	{
		m_gameStates.push_back(m_nextState);
		m_gameStates.back()->OnEnter();
	}
};

#endif /* defined(__GameStateMachine__) */