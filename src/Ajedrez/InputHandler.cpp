#include "InputHandler.h" 

#include <iostream>
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

void InputHandler::InitialiseJoysticks()
{
	// Nos aseguramos de que el subsistema de joystick esté iniciado
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	// Si hay mandos disponibles, los añadimos a la lista
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			// Por cada mando, lo añadimos a la lista junto a los valores de sus joysticks
			SDL_Joystick* joy = SDL_JoystickOpen(i);
			if (joy != NULL)
			{
				// Añadir a la lista de mandos
				m_joysticks.push_back(joy);
				// Añadir los joysticks
				m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); // add our pair
				// Y los botones
				std::vector<bool> tempButtons;
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}
				m_buttonStates.push_back(tempButtons);
				// Y las crucetas
				m_hatStates.push_back(0);
			}
			else
			{
				std::cout << SDL_GetError();
			}
		}
		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoysticksInitialised = true;
		std::cout << "Initialised " << m_joysticks.size() << " joystick(s)\n";
	}
	// Si no, pues nada
	else
	{
		m_bJoysticksInitialised = false;
	}
}

int InputHandler::Xvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->GetX();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->GetX();
		}
	}
	return 0;
}

int InputHandler::Yvalue(int joy, int stick)
{
	if (m_joystickValues.size() > 0)
	{
		if (stick == 1)
		{
			return m_joystickValues[joy].first->GetY();
		}
		else if (stick == 2)
		{
			return m_joystickValues[joy].second->GetY();
		}
	}
	return 0;
}

void InputHandler::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Game::Instance()->Quit();
		}
		// Botón pulsado
		if (event.type == SDL_JOYBUTTONDOWN)
		{
#if _DEBUG
			std::cout << "Boton " << (int)event.jbutton.button << std::endl;
#endif
			int whichOne = event.jaxis.which;
			m_buttonStates[whichOne][event.jbutton.button] = true;
		}
		
		// Botón levantado
		if (event.type == SDL_JOYBUTTONUP)
		{
			int whichOne = event.jaxis.which;
			m_buttonStates[whichOne][event.jbutton.button] = false;
		}
		// Cruceta
		if(event.type == SDL_JOYHATMOTION)
		{
#if _DEBUG
			std::cout << "Hat " << (int)event.jhat.value << std::endl;
#endif
			int whichOne = event.jhat.which;
			m_hatStates[whichOne] = (int)event.jhat.value;
		}

		// Movimiento de joystick
		if (event.type == SDL_JOYAXISMOTION)
		{
			/* Por ahora, esto está transformando la señal analógica del mando
			a una digital (0/1) teniendo en cuenta la deadzone */
			int whichOne = event.jaxis.which;
			std::cout << "- AxisMotion del mando " << whichOne << " -\n";

			/* JOYSTICK IZQUIERDO (.first) */
			// izquierda/derecha
			if (event.jaxis.axis == 0)
			{
				// Movimiento teniendo en cuenta las zonas muertas; lo convertimos de analógico a digital
				if (event.jaxis.value > m_joystickDeadZone)
				{
					m_joystickValues[whichOne].first->SetX(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[whichOne].first->SetX(-1);
				}
				else
				{
					m_joystickValues[whichOne].first->SetX(0);
				}
			}

			// arriba/abajo
			if (event.jaxis.axis == 1)
			{
				if (event.jaxis.value > m_joystickDeadZone)
				{
					m_joystickValues[whichOne].first->SetY(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[whichOne].first->SetY(-1);
				}
				else
				{
					m_joystickValues[whichOne].first->SetY(0);
				}
			}
			/* JOYSTICK DERECHO (.second) */
			// izquierda/derecha
			if (event.jaxis.axis == 2)
			{
				if (event.jaxis.value > m_joystickDeadZone)
				{
					m_joystickValues[whichOne].second->SetX(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[whichOne].second->SetX(-1);
				}
				else
				{
					m_joystickValues[whichOne].second->SetX(0);
				}
			}

			// arriba/abajo
			if (event.jaxis.axis == 3)
			{
				if (event.jaxis.value > m_joystickDeadZone)
				{
					m_joystickValues[whichOne].second->SetY(1);
				}
				else if (event.jaxis.value < -m_joystickDeadZone)
				{
					m_joystickValues[whichOne].second->SetY(-1);
				}
				else
				{
					m_joystickValues[whichOne].second->SetY(0);
				}
			}

#if _DEBUG
			// Información de depuración
			/*
			std::cout << "Izquierdo: (" << m_joystickValues[whichOne].first->GetX() << "," <<
				m_joystickValues[whichOne].first->GetY() << ") | Derecho: (" <<
				m_joystickValues[whichOne].second->GetX() << "," << 
				m_joystickValues[whichOne].second->GetY() << ")" << std::endl;
			*/
#endif
		}
	}
}

void InputHandler::Clean()
{
	if (m_bJoysticksInitialised)
	{
		for (unsigned int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}