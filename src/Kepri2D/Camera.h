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
	void Update(Vector2D velocity);

	//Setters
	/* Establece el objetivo al que seguir� la c�mara */
	inline void SetTarget(Vector2D* target) { m_pTarget = target; }
	/* Mueve la c�mara a la posici�n dada */
	inline void SetPosition(const Vector2D& position) { m_position = position; }

	//Getters
	/* Posici�n actual de la c�mara */
	const Vector2D GetPosition() const;

	// Para destruir la instancia
	void Clean()
	{
		if(s_pInstance != nullptr)
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}

private:
	/* Instancia del singleton */
	static Camera* s_pInstance;

	/* Constructora y destructora privadas */
	Camera() : m_position(0,0), m_pTarget(nullptr) {}
	~Camera(){}

	/* Posici�n de la c�mara */
	Vector2D m_position;

	/* Posici�n del objetivo */
	Vector2D* m_pTarget;
};

#endif