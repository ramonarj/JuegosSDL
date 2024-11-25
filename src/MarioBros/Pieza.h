#ifndef __PIEZA__
#define __PIEZA__

#include "Kepri2D.h"

/* Hereda de GameObject */
class Pieza : public GameObject
{
public:

	/* Constructora */
	Pieza() : GameObject() {}
	virtual void Load(const LoaderParams* pParams) override;

	/* Heredadas*/
	/* Por ahora, es una prueba de movimiento */
	virtual void Update() override;

	void OnCollision(const GameObject* other) override;

	// Obligado
	virtual std::string Type() const override{ return "Pieza"; }

private:
	// Para el input
	void HandleInput();

	// Para pruebas
	void InputConMando();
	void InputConRaton();
	void InputConTeclado();
	Vector2D initialVel;
	Vector2D prevVel;
};


class PiezaCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new Pieza();
	}
};


#endif /* defined(__Pieza__) */