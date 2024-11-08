#ifndef __ANIMATEDGRAPHIC__
#define __ANIMATEDGRAPHIC__

#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject
{
public:
	// No me deja usar las listas de inicializaci�n en el .cpp
	AnimatedGraphic(const LoaderParams* pParams, float animSpeed) :SDLGameObject(pParams)
	{
		m_numFrames = pParams->getNumFrames();
		m_animSpeed = animSpeed;
	}
	/* Heredado */
	virtual void Update();

protected:
	/* N�mero de frames de animaci�n */
	int m_numFrames;
	/* N�mero de frames/segundo */
	float m_animSpeed;
};

#endif /* defined(__AnimatedGraphic__) */