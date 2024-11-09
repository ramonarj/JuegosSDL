#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include "GameState.h"
#include "AnimatedGraphic.h"
#include "Pieza.h"


class PlayState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return s_playID; }

	// Para llamarlo desde Pieza
	void PiezaSeleccionada(Pieza* pieza);

private:
	static const std::string s_playID;

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;

	// Constantes
	const int ANCHO_PIEZA = 45;
	const int ALTO_PIEZA = 62;
	const int TAM_CASILLA = 55;
	const int BORDE_TABLERO = 32;

	// Variables
	AnimatedGraphic* m_fondoTablero;
	AnimatedGraphic* m_seleccion;
	Pieza* m_piezaSeleccionada;
	Pieza* piezaViva;
	/* A quién le toca mover */
	equipo_pieza m_turno;

	// Metodos auxiliares
	void LeeTablero(std::string fileName);

	/* Comprobación de colisiones entre 2 gameobjects */
	bool CheckCollision(SDLGameObject* p1, SDLGameObject* p2);
};


#endif /* defined(__PlayState__) */