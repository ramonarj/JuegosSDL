#ifndef __ANIMATEDGRAPHIC__
#define __ANIMATEDGRAPHIC__

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	/* Constructora por defecto */
	AnimatedGraphic() : SDLGameObject(), m_numFrames(1), m_animSpeed(0) {}

	/* Heredados */
	virtual void Load(const LoaderParams* pParams);

	virtual void Update();

protected:

	/* Número de frames de animación */
	int m_numFrames;
	/* Número de frames/segundo */
	int m_animSpeed;
};


class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new AnimatedGraphic();
	}
};


#endif /* defined(__AnimatedGraphic__) */