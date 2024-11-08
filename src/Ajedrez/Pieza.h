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
		initialVel = Vector2D(1, 1);
		m_velocity = initialVel;
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
	void InputConTeclado();
	Vector2D initialVel;
	Vector2D prevVel;
};

#endif /* defined(__Pieza__) */