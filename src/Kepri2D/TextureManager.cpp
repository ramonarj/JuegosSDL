#include "TextureManager.h"

#include "SDL_image.h"

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::Load(std::string fileName, std::string id, SDL_Renderer* pRenderer, bool absoluteRoute)
{
	// Si solo dan el nombre de la imagen, est� en la carpeta de im�genes
	if (!absoluteRoute)
		fileName = IMAGES_PATH + fileName;

	// Creamos la textura con SDL_Image a partir de una surface
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0)
	{
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	// Si todo ha ido bien, la a�adimos al map
	if(pTexture != 0)
	{
		m_textureMap[id] = pTexture;
		return true;
	}
	return false; //algo fall�
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0,0, width, height }; //x, y, w, h
	SDL_Rect destRect = { x, y, width, height };
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height,
	int row, int col, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	// Rect�ngulos fuente y destino
	SDL_Rect srcRect = {col * width, row * height, width, height };
	SDL_Rect destRect = { x, y, width, height };
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::DrawTile(std::string id, int margin, int spacing, 
	int x, int y, int width, int height, int row, int col, SDL_Renderer* pRenderer)
{
	// rect�ngulo fuente
	SDL_Rect srcRect;
	srcRect.x = margin + (spacing + width) * col;
	srcRect.y = margin + (spacing + height) * row;
	srcRect.w = width;
	srcRect.h = height;

	// rect�ngulo destino
	SDL_Rect destRect = { x, y, width, height };

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}