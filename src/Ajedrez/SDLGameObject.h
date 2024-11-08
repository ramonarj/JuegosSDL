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
	SDLGameObject() : GameObject() {}

	virtual void Load(const LoaderParams* pParams);

	// Heredados de GameObject
	virtual void Update();
	virtual void Draw();
	virtual void Clean(){}

	/* Getters */
	inline Vector2D& GetPosition() { return m_position; }
	inline int GetWidth() { return m_width; }
	inline int GetHeight() { return m_height; }

protected:
	/* 'Protected' porque queremos que otras clases puedan heredar de SDLGameObject
y acceder a las variables de este */
	/* Posición */
	Vector2D m_position;
	/* Velocidad */
	Vector2D m_velocity;
	/* Aceleración */
	Vector2D m_acceleration;

	/* Tamaño en píxeles que ocupará en pantalla */
	int m_width;
	int m_height;

	/* Fila y columna de la textura que se usarán para pintar la entidad */
	int m_textureRow;
	int m_textureCol;

	/* Identificador de la textura usada */
	std::string m_textureID;
};

#endif