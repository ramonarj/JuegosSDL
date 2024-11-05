#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include <iostream>
#include <string>

#include "SDL.h"

class GameObject
{
public:

	/* Crea un GameObject con su posición, dimensiones y textura */
	void Load(int x, int y, int width, int height, std::string textureID);

	/* Dibuja el GameObject */
	void Draw(SDL_Renderer* pRenderer);
	/* Actualiza el GameObject */
	void update() { std::cout << "update game object"; }
	/* Destruye y limpia el GameObject */
	void clean() { std::cout << "clean game object"; }

	// Funciones provisionales
	inline void SetPos(int x, int y) { m_x = x; m_y = y; }
	inline int GetPosX() { return m_x; }
	inline int GetPosY() { return m_y; }

	//idem
	inline void SetTextureFrame(int row, int col) { m_textureRow = row; m_textureCol = col; }

protected:
	/* 'Protected' porque queremos que otras clases puedan heredar de GameObject
	y acceder a las variables de este */

	// Posición
	int m_x;
	int m_y;

	// Tamaño
	int m_width;
	int m_height;

	// Frame de la textura que se está usando
	int m_textureCol;
	int m_textureRow;

	std::string m_textureID;
};


#endif /* defined(__GameObject__) */
