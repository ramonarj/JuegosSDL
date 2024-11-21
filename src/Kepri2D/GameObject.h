#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "LoaderParams.h"
#include "Vector2D.h"

/* Clase abstracta y completamente genérica para un GameObject. Sirve tanto si usamos SDL
como si usamos cualquier otro motor/librería */
class GameObject
{
/* Los métodos son virtuales para poder usar el polimorfismo */
public:

	virtual ~GameObject(){}

	/* Inicializa el GameObject */
	virtual void Load(const LoaderParams* pParams);

	/* Dibuja el GameObject */
	virtual void Draw();
	/* Actualiza el GameObject */
	virtual void Update();
	/* Destruye y limpia el GameObject */
	virtual void Clean(){}

	/* Getters (anteriormente en SDLGameObject) */
	inline Vector2D& GetPosition() { return m_position; }
	inline int GetWidth() { return m_width; }
	inline int GetHeight() { return m_height; }

protected:
	GameObject() : m_position(0,0), m_velocity(0,0), m_acceleration(0,0),
	m_width(0), m_height(0), m_textureRow(0), m_textureCol(0), m_angle(0), m_alpha(255) {}

	/* Posición */
	Vector2D m_position;
	/* Velocidad */
	Vector2D m_velocity;
	/* Aceleración */
	Vector2D m_acceleration;

	/* Tamaño en píxeles del frame que se va a usar para el GameObject */
	int m_frameWidth;
	int m_frameHeight;

	/* Tamaño en píxeles que ocupará ell GameObject en pantalla */
	int m_width;
	int m_height;

	/* Fila y columna de la textura que se usarán para pintar la entidad */
	int m_textureRow;
	int m_textureCol;

	/* Identificador de la textura usada */
	std::string m_textureID;

	/* Rotación horaria, en grados, del GameObject {0-360} */
	double m_angle;
	/* Nivel de transparencia {0 - 255} */
	int m_alpha;
};

#endif /* defined(__GameObject__) */
