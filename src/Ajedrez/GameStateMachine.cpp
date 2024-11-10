#include "GameStateMachine.h"

#include <iostream>

void GameStateMachine::PushState(GameState* pState)
{
	m_transitionType = PUSH;
	m_nextState = pState;
}

void GameStateMachine::PopState()
{
	m_transitionType = POP;
}

void GameStateMachine::ChangeState(GameState* pState)
{
	// si es el mismo estado, no lo metemos
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->GetStateID() == pState->GetStateID())
		{
			return; // do nothing
		}
	}
	// para cuando termine el frame
	m_transitionType = CHANGE;
	m_nextState = pState;
}

void GameStateMachine::ChangeStatePrivate()
{
	switch(m_transitionType)
	{
	case PUSH:
		Push();
		break;
	case POP:
		if (!m_gameStates.empty())
		{
			Pop();
		}
		break;
	case CHANGE:
		// Es un while por si el estado en que estamos ha sido pusheado,
		// en cuyo caso hay que borrar más de uno de la pila
		while (!m_gameStates.empty())
		{
			Pop();
		}
		Push();
		break;
	default:
		break;
	}

	// clean requests
	m_nextState = nullptr;
	m_transitionType = NONE;
}

void GameStateMachine::Update()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->Update();
	}
	// alguien ha pedido cambiar de estado en este frame
	if (m_transitionType != NONE)
		ChangeStatePrivate();
}

void GameStateMachine::Render()
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->Render();
	}
}