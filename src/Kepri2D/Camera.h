#ifndef __CAMERA__
#define __CAMERA__

#include "Vector2D.h"

/* Clase singleton que representa la cámmara de la escena */
class Camera
{
public:

	static Camera* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new Camera();
		return s_pInstance;
	}

	// ?
	void Update();

	//Setters
	/* Establece el objetivo al que seguirá la cámara */
	inline void SetTarget(Vector2D* target) { m_pTarget = target; }

	/* Mueve la cámara a la posición dada */
	inline void SetPosition(const Vector2D& position) { m_position = position; }

	/* Cambia el color de fondo de la escena */
	void SetBackgroundColor(uint32_t color);

	//Getters
	/* Posición actual de la cámara */
	const Vector2D GetPosition() const;

	/* Convierte una posición global en una coordenada de la pantalla */
	Vector2D WorldToScreen(const Vector2D& pos);

	/* Fija unos límites para que la cámara no se salga del rectángulo dado */
	void SetLimits(const Vector2D& upperLeft, const Vector2D& lowerRight);

	// Para destruir la instancia
	void Clean();

private:
	/* Instancia del singleton */
	static Camera* s_pInstance;

	/* Constructora y destructora privadas */
	Camera() : m_position(0,0), m_pTarget(nullptr),
		m_lowerLimit(-FLT_MAX, -FLT_MAX), m_upperLimit(FLT_MAX, FLT_MAX){}
	~Camera(){}

	/* Posición de la cámara */
	Vector2D m_position;

	/* Posición del objetivo */
	Vector2D* m_pTarget;

	/* Límites de la cámara; son mutables en cualquier momento */
	Vector2D m_lowerLimit;
	Vector2D m_upperLimit;
};

#endif