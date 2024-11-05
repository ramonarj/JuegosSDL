#ifndef __SDLGAMEOBJECT__
#define __SDLGAMEOBJECT__

#include "GameObject.h"
#include "SDL.h"
#include <string>
#include "Vector2D.h"

/* GameObject específico para usar con SDL */
class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);

	// Heredados de GameObject
	virtual void Draw();
	virtual void Update(){}
	virtual void Clean(){}

	inline void SetTextureFrame(int row, int col) { m_textureRow = row; m_textureCol = col; }

protected:
	/* 'Protected' porque queremos que otras clases puedan heredar de SDLGameObject
y acceder a las variables de este */
	// Posición
	Vector2D m_position;

	// Tamaño
	int m_width;
	int m_height;

	// Frame actual
	int m_textureRow;
	int m_textureCol;

	// Nombre de la textura
	std::string m_textureID;
};

#endif