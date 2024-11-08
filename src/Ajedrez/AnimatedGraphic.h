#ifndef __ANIMATEDGRAPHIC__
#define __ANIMATEDGRAPHIC__

#include "SDLGameObject.h"

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

#endif /* defined(__AnimatedGraphic__) */