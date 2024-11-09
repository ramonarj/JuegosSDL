#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__

#include <string>
#include "SDL.h"
#include <map>

static std::string IMAGES_PATH = "../../bin/assets/images/";

/* Clase Singleton para la gestión de texturas del juego */
class TextureManager
{
public:
	/* Devuelve un puntero a la instancia */
	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	/* Carga una textura a partir de una imagen y la almacena con el identificador dado */
	bool Load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	/* Elimina una textura del diccionario */
	inline void ClearFromTextureMap(std::string id) { m_textureMap.erase(id); }

	/* Dibuja la textura entera en el rectángulo destino dado */
	void Draw(std::string id, int x, int y, int width, int height, 
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/* Dibuja un fotograma de la textura con los parámetros dados */
	void DrawFrame(std::string id, int x, int y, int width, int height, 
		int row, int col, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	/* Constructora privada; solo se puede acceder a la clase con Instance() */
	TextureManager() {}
	static TextureManager* s_pInstance;
	/* Diccionario de punteros a texturas */
	std::map<std::string, SDL_Texture*> m_textureMap;
};


#endif /* defined(__TextureManager__) */
