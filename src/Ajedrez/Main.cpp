#include "Game.h"
#include <iostream>

// Esto es por si quiero usar un main normal y no la macro de SDL
// #undef main


int main(int argc, char* args[])
{
	// Inicializar el juego
	std::cout << "game init attempt...\n";
	if(Game::Instance()->Init("Ajedrez", 100, 100, 640, 480, false))
	{
		// Bucle principal
		std::cout << "game init success!\n";
		while (Game::Instance()->Running())
		{
			Game::Instance()->HandleInput();
			Game::Instance()->Update();
			Game::Instance()->Render();

			SDL_Delay(10); // pequeño delay para limitar la tasa de fotogramas
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