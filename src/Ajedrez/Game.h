#ifndef __GAME__
#define __GAME__

#include <vector>
#include "Pieza.h"

/* Clase singleton para la gestión del juego */
class Game
{
public:

	/* Devuelve la instancia */
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	~Game(){}

	/* Inicializa SDL y crea la ventana y el renderer */
	bool Init(const char* title, int xpos, int ypos, 
		int height, int width, bool fullscreen);

	/* Lee el input del usuario */
	void HandleInput();
	/* Actualiza la lógica y las físicas del juego */
	void Update();
	/* Pinta el estado actual del juego en la ventana */
	void Render();
	/* Limpia el código y cierra el juego */
	void Clean();

	/* ¿Está el juego ejecutándose? */
	bool Running() { return m_bRunning; }

	/* Getters */
	SDL_Renderer* GetRenderer() const { return m_pRenderer; }

private:

	Game() {}
	static Game* s_pInstance;

	// Variables (g = global, m = member, p = pointer, b = bool, s = singleton)
	// SDL
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	// Lista de GameObjects
	std::vector<GameObject*> m_gameObjects;

	Pieza* caballo;
	SDLGameObject* piezaCambiante;

	// Cambio de frame para la pieza
	int frameCol;
	int frameRow;

	// Prueba de vectores
	Vector2D v1;
};


#endif /* defined(__Game__) */