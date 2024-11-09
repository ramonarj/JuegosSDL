#ifndef __ANIMATEDGRAPHIC__
#define __ANIMATEDGRAPHIC__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic() : SDLGameObject() {}

	// No me deja usar las listas de inicializaci�n en el .cpp
	virtual void Load(const LoaderParams* pParams);

	/* Heredado */
	virtual void Update();

protected:

	/* N�mero de frames de animaci�n */
	int m_numFrames;
	/* N�mero de frames/segundo */
	float m_animSpeed;
};


class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new AnimatedGraphic();
	}
};


#endif /* defined(__AnimatedGraphic__) */