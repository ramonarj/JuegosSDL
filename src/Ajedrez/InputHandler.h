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

	/* Mando de la PS2:
		0 -> Equis
		1 -> Círculo
		2 -> Cuadrado
		3 -> Triángulo
		4 -> L1
		5 -> R1
		6 -> L2
		7 -> R2
		8 -> SELECT
		9 -> START
		10 -> L3
		11 -> R3
		12 -> ANALOG
		A partir de 13 -> error out of range 
		Por desgracia, la cruceta no está mapeada (debería haber 17 botones y solo hay 13)
	*/
	inline bool GetButtonState(int joy, int buttonNumber)
	{
		return m_buttonStates[joy][buttonNumber];
	}

	/* Devuelve la flecha de la cruceta que se está pulsando (solo se pulsa 1 a la vez) 
	0 -> Ninguna
	1 -> Arriba
	2 -> Derecha
	4 -> Abajo
	8 -> Izquierda
	*/
	inline int GetHat(int joy)
	{
		return m_hatStates[joy];
	}


private:
	InputHandler(){}
	~InputHandler() {}

	bool m_bJoysticksInitialised;

	/* Instancia */
	static InputHandler* s_pInstance;

	/* Lista de mandos conectados */
	std::vector<SDL_Joystick*> m_joysticks;
	/* Posiciones de los joysticks de cada mando*/
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	/* Estado de los botones de cada mando (pulsados/no) */
	std::vector<std::vector<bool>> m_buttonStates;
	/* Estado de las crucetas de cada mando */
	std::vector<int> m_hatStates;

	/* Zonas muertas */
	const int m_joystickDeadZone = 10000;
};

#endif /* defined(__InputHandler__) */