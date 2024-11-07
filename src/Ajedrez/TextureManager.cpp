#include "TextureManager.h"

#include "SDL_image.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::Load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	// Creamos la textura con SDL_Image a partir de una surface
	SDL_Surface* pTempSurface = IMG_Load((IMAGES_PATH + fileName).c_str());
	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	// Si todo ha ido bien, la añadimos al map
	if(pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	return false; //algo falló
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0,0, width, height }; //x, y, w, h
	SDL_Rect destRect = { x, y, width, height };
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height,
	int row, int col, SDL_Renderer* pRenderer, bool centered, SDL_RendererFlip flip)
{
	// Rectángulos fuente y destino
	SDL_Rect srcRect = {col * width, row * height, width, height };
	if(centered)
	{
		x -= (width / 2);
		y -= (height / 2);
	}
	SDL_Rect destRect = { x, y, width, height };
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}