#include "GameStateMachine.h"

void GameStateMachine::PushState(GameState* pState)
{
	/*
	m_gameStates.push_back(pState);
	m_gameStates.back()->OnEnter();
	*/

	m_transitionType = PUSH;
	m_nextState = pState;
}

void GameStateMachine::PopState()
{
	/*
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->OnExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
	*/

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
	// Si es un pop() o change(), eliminamos y sacamos el estado anterior
	if(m_transitionType == POP || m_transitionType == CHANGE)
	{
		if (!m_gameStates.empty())
		{
			// delete old state
			if (m_gameStates.back()->OnExit())
			{
				delete m_gameStates.back();
				m_gameStates.pop_back();
			}
		}
	}

	// Si es un push() o change(), metemos el nuevo estado y lo inicializamos
	if(m_transitionType != POP)
	{
		m_gameStates.push_back(m_nextState);
		m_gameStates.back()->OnEnter();
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