#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__

#include <string>
#include "SDL.h"
#include <map>

static std::string IMAGES_PATH = "../../bin/Assets/";

class TextureManager
{
public:
	/* Carga una textura a partir de una imagen y la almacena con el identificador dado */
	bool Load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	/* Dibuja la textura entera en el rectángulo destino dado */
	void Draw(std::string id, int x, int y, int width, int height, 
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/* Dibuja un fotograma de la textura con los parámetros dados */
	void DrawFrame(std::string id, int x, int y, int width, int height, 
		int row, int col, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);


private:
	std::map<std::string, SDL_Texture*> m_textureMap;
};


#endif /* defined(__TextureManager__) */
