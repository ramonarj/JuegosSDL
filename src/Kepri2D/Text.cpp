#include "Text.h"

#include "SDL_ttf.h"
#include "Game.h"

Text::Text()
{
	// Tamaño de la letra
	float ptsize = 30;

	// Color para el texto
	SDL_Color white = { 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE };
	// Fuente a utilizar
	TTF_Font* font = TTF_OpenFont((FONTS_PATH + "ARCADECLASSIC.ttf").c_str(), ptsize);

	// Texto
	SDL_Surface* text = TTF_RenderText_Solid(font, "Holita", white);

	// Textura que se pintará
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), text);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 200; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(Game::Instance()->GetRenderer(), Message, NULL, &Message_rect);
	SDL_RenderPresent(Game::Instance()->GetRenderer());

	Game::Instance()->DelayFor(2000);

	std::cout << "e";
}