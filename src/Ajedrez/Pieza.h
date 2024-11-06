#ifndef __PIEZA__
#define __PIEZA__

#include "SDLGameObject.h"

enum tipo_pieza
{
	Peon, Torre, Cabllo, Alfil, Reina, Rey
};

enum equipo_pieza
{
	Blancas, Negras
};


/* Hereda de GameObject */
class Pieza : public SDLGameObject
{
public:

	/* Constructora */
	Pieza(const LoaderParams* pParams, tipo_pieza tipo, equipo_pieza equipo);

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

	// Cambio de frame para la pieza
	int frameCol;
	int frameRow;

	//tipo
	tipo_pieza m_tipo;
};

#endif /* defined(__Pieza__) */