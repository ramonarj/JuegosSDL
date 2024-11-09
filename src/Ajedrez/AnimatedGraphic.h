#ifndef __ANIMATEDGRAPHIC__
#define __ANIMATEDGRAPHIC__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic() : SDLGameObject() {}

	// No me deja usar las listas de inicialización en el .cpp
	virtual void Load(const LoaderParams* pParams);

	/* Heredado */
	virtual void Update();

protected:

	/* Número de frames de animación */
	int m_numFrames;
	/* Número de frames/segundo */
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