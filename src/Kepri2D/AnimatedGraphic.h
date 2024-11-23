#ifndef __ANIMATEDGRAPHIC__
#define __ANIMATEDGRAPHIC__

#include "GameObject.h"
#include "GameObjectFactory.h"
#include "../../dependencies/SDL2-2.30.9/include/SDL.h"

class AnimatedGraphic : public GameObject
{
public:
	/* Constructora por defecto */
	AnimatedGraphic() : GameObject(), m_numFrames(1), m_animSpeed(0) {}

	/* Heredados */
	virtual void Load(const LoaderParams* pParams);

	// Obligado
	virtual std::string Type() const { return "AnimatedGraphic"; }

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