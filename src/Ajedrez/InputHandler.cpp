#include "InputHandler.h" 

#include <iostream>
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler() : m_keystates(nullptr), m_bJoysticksInitialised(false)
{
	// Inicializar ratón
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
	m_mousePosition = new Vector2D(0, 0);
}

void InputHandler::Reset()
{
	// Devolver los botones del ratón al estado inicial
	for (int i = 0; i < 3; i++)
		m_mouseButtonStates[i] = false;
}


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
			return (int)m_joystickValues[joy].first->GetX();
		}
		else if (stick == 2)
		{
			return (int)m_joystickValues[joy].second->GetX();
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
			return (int)m_joystickValues[joy].first->GetY();
		}
		else if (stick == 2)
		{
			return (int)m_joystickValues[joy].second->GetY();
		}
	}
	return 0;
}

bool InputHandler::IsKeyDown(SDL_Scancode key)
{
	// Comprobar que tiene la referencia al teclado
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void InputHandler::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			// Cruz roja de la ventana
		case SDL_QUIT:
			Game::Instance()->Quit();
			break;
			/* EVENTOS DEL TECLADO */
			// Simplemente actualizamos el array de teclas
		case SDL_KEYDOWN:
			m_keystates = (Uint8*)SDL_GetKeyboardState(0);
			break;
		case SDL_KEYUP:
			m_keystates = (Uint8*)SDL_GetKeyboardState(0);
			break;
			/* EVENTOS DEL RATÓN */
			// Movimiento 
		case SDL_MOUSEMOTION:
			OnMouseMove(event);
			break;
			// Botón pulsado
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown(event);
			break;
			// Botón levantado
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp(event);
			break;
			/* EVENTOS DEL MANDO */
			// Joysticks
		case SDL_JOYAXISMOTION:
			OnJoystickAxisMove(event);
			break;
			// Botón pulsado
		case SDL_JOYBUTTONDOWN:
			OnJoystickButtonDown(event);
			break;
			// Botón levantado
		case SDL_JOYBUTTONUP:
			OnJoystickButtonUp(event);
			break;
			// Cruceta
		case SDL_JOYHATMOTION:
			OnJoystickHatMove(event);
			break;
		default:
			break;
		}
	}
}

void InputHandler::OnMouseMove(SDL_Event& event)
{
	m_mousePosition->SetX((float)event.motion.x);
	m_mousePosition->SetY((float)event.motion.y);
}

void InputHandler::OnMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::OnMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::OnJoystickAxisMove(SDL_Event& event)
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

void InputHandler::OnJoystickButtonDown(SDL_Event& event)
{
#if _DEBUG
	std::cout << "Boton " << (int)event.jbutton.button << std::endl;
#endif
	int whichOne = event.jaxis.which;
	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::OnJoystickButtonUp(SDL_Event& event)
{
	int whichOne = event.jaxis.which;
	m_buttonStates[whichOne][event.jbutton.button] = false;
}

void InputHandler::OnJoystickHatMove(SDL_Event& event)
{
#if _DEBUG
	std::cout << "Hat " << (int)event.jhat.value << std::endl;
#endif
	int whichOne = event.jhat.which;
	m_hatStates[whichOne] = (int)event.jhat.value;
}


void InputHandler::Clean()
{
	if (m_bJoysticksInitialised)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}