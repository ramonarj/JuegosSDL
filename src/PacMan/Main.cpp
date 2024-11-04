#include<iostream>
#include "Game.h"

// Esto es por si quiero usar un main normal y no la macro de SDL
// #undef main

Game* g_game = 0;

int main(int argc, char* args[])
{
	// Inicializar el juego
	g_game = new Game();
	g_game->Init("Ajedrez", 100, 100, 640, 480, 0);

	// Bucle principal
	while(g_game->Running())
	{
		g_game->HandleInput();
		g_game->Update();
		g_game->Render();
	}

	// Limpiar y salimos
	g_game->Clean();

	return 0;
}