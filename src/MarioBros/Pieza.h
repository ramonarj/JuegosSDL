#ifndef __PIEZA__
#define __PIEZA__

#include "../Kepri2D/SDLGameObject.h"
#include "../Kepri2D/GameObjectFactory.h"

/* Hereda de GameObject */
class Pieza : public SDLGameObject
{
public:

	/* Constructora */
	Pieza() : SDLGameObject() {}
	virtual void Load(const LoaderParams* pParams);

	/* Heredadas*/
	virtual void Draw();
	/* Por ahora, es una prueba de movimiento */
	virtual void Update();
	//void Draw(SDL_Renderer* pRenderer) {}
	virtual void Clean(){}

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