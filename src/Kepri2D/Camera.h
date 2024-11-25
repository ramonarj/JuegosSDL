#ifndef __CAMERA__
#define __CAMERA__

#include "Vector2D.h"

/* Clase singleton que representa la c�mmara de la escena */
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
	/* Establece el objetivo al que seguir� la c�mara */
	inline void SetTarget(Vector2D* target) { m_pTarget = target; }

	/* Mueve la c�mara a la posici�n dada */
	inline void SetPosition(const Vector2D& position) { m_position = position; }

	/* Cambia el color de fondo de la escena */
	void SetBackgroundColor(uint32_t color);

	//Getters
	/* Posici�n actual de la c�mara */
	const Vector2D GetPosition() const;

	/* Convierte una posici�n global en una coordenada de la pantalla */
	Vector2D WorldToScreen(const Vector2D& pos);

	/* Fija unos l�mites para que la c�mara no se salga del rect�ngulo dado */
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

	/* Posici�n de la c�mara */
	Vector2D m_position;

	/* Posici�n del objetivo */
	Vector2D* m_pTarget;

	/* L�mites de la c�mara; son mutables en cualquier momento */
	Vector2D m_lowerLimit;
	Vector2D m_upperLimit;
};

#endif