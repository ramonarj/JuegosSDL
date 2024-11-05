#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__

#include <vector>
#include "SDL.h"
#include "Vector2D.h"

/* Clase Singleton para gestionar los dispositivos de entrada (mandos, ratón, etc) */
class InputHandler
{
public:
	/* Devuelve la instancia */
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
			return s_pInstance;
		}
		return s_pInstance;
	}

	void Update();
	/* Cierra los dispositivos */
	void Clean();

	/* Mandos */
	/* Comprueba si hay mandos conectados y los registra */
	void InitialiseJoysticks();
	inline bool JoysticksInitialised() { return m_bJoysticksInitialised; }

	/* Getters de cada mando */
	int Xvalue(int joy, int stick);
	int Yvalue(int joy, int stick);


private:
	InputHandler(){}
	~InputHandler() {}

	bool m_bJoysticksInitialised;

	/* Instancia */
	static InputHandler* s_pInstance;

	/* Vector de mandos conectados y las posiciones de los joysticks */
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;

	/* Zonas muertas */
	const int m_joystickDeadZone = 10000;
};

#endif /* defined(__InputHandler__) */