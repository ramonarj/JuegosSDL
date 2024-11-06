#ifndef __PIEZA__
#define __PIEZA__

#include "SDLGameObject.h"

/* Hereda de GameObject */
class Pieza : public SDLGameObject
{
public:

	/* Constructora */
	Pieza(const LoaderParams* pParams) : SDLGameObject(pParams) 
	{
		frameRow = 0;
		frameCol = 0;
		initialVel = Vector2D(1, 1);
		m_velocity = initialVel;
		//m_acceleration = Vector2D(1, 1); 
	}

	/* Heredadas*/
	virtual void Draw();
	/* Por ahora, es una prueba de movimiento */
	virtual void Update();
	//void Draw(SDL_Renderer* pRenderer) {}
	virtual void Clean(){}

private:
	// Para el input
	void HandleInput();

	// Para pruebas
	void InputConMando();
	void InputConRaton();
	Vector2D initialVel;
	Vector2D prevVel;

	// Cambio de frame para la pieza
	int frameCol;
	int frameRow;
};

#endif /* defined(__Pieza__) */