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
	virtual void Update();
	virtual void Draw();
	virtual void Clean(){}

	//Nuevo
	inline bool IsActive() { return m_active; }
	inline void SetActive(bool active) { m_active = active; }

	inline void SetPosition(Vector2D position) { m_position = position; }
	inline Vector2D GetPosition() { return m_position; }

protected:
	/* 'Protected' porque queremos que otras clases puedan heredar de SDLGameObject
y acceder a las variables de este */
	// Posición y velocidad
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	// Tamaño
	int m_width;
	int m_height;

	// Frame actual
	int m_textureRow;
	int m_textureCol;

	// Nombre de la textura
	std::string m_textureID;

	// Métodos auxiliares
	inline void SetTextureFrame(int row, int col) { m_textureRow = row; m_textureCol = col; }

	// Si está activo o no
	bool m_active;
};

#endif