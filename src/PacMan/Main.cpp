#include<iostream>
#include "SDL.h"


// Esto es por si quiero usar un main normal y no la macro de SDL
#undef main

int main()
{
	std::cout << "SDL";
	return 0;
}