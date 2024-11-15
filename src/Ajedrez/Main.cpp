#include "Game.h"
#include <iostream>
#include "checkML.h"

// Esto es por si quiero usar un main normal y no la macro de SDL
// #undef main

const int FPS = 60;
const int DELAY_TIME = int(1000.0f / FPS);

int main(int argc, char* args[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	/* Esto de abajo sirve para crear un punto de interrupción(al depurar)
	en la línea que reserva la memoria (new/malloc) que se queda sin borrar
	con el 'memory allocation number' {158} */
	//_crtBreakAlloc = 1169;

	Uint32 frameStart, frameTime = 0;

	// Inicializar el juego
	std::cout << "game init attempt...\n";
	if(Game::Instance()->Init("Ajedrez", 100, 100, 640, 480, false))
	{
		// Bucle principal
		std::cout << "game init success!\n";
		while (Game::Instance()->Running())
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->HandleInput();
			Game::Instance()->Update();
			Game::Instance()->Render();

			frameTime = SDL_GetTicks() - frameStart;

			// pequeño delay para limitar la tasa de fotogramas
			if (frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else // algo ha salido mal
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}

	// Limpiar y salimos
	std::cout << "game closing...\n";
	Game::Instance()->Clean();

	return 0;
}