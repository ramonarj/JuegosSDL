#ifndef __PIEZA__
#define __PIEZA__

#include "SDLGameObject.h"
class PlayState;

enum tipo_pieza
{
	Peon, Torre, Caballo, Alfil, Reina, Rey
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
	Pieza(const LoaderParams* pParams, tipo_pieza tipo, equipo_pieza equipo, Vector2D posTablero, PlayState* const playState);

	/* Heredadas*/
	virtual void Draw();
	/* Por ahora, es una prueba de movimiento */
	virtual void Update();
	//void Draw(SDL_Renderer* pRenderer) {}
	virtual void Clean(){}

private:
	// Para el input
	void HandleInput();

	// Cambio de frame para la pieza
	int frameCol;
	int frameRow;

	//tipo
	tipo_pieza m_tipo;
	// Posición que ocupa en el tablero
	Vector2D m_posTablero;
	// referencia al playstate
	PlayState* m_playState;

	// Funciones auxiliares
	bool DentroTablero(Vector2D pos);
};

#endif /* defined(__Pieza__) */