#ifndef __ANIMATEDGRAPHIC__
#define __ANIMATEDGRAPHIC__

#include "GameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public GameObject
{
public:
	/* Constructora por defecto */
	AnimatedGraphic() : GameObject(), m_numFrames(1), m_animSpeed(0) {}

	/* Heredados */
	virtual void Load(const LoaderParams* pParams) override;

	// Obligado
	virtual std::string Type() const override{ return "AnimatedGraphic"; }

	virtual void Update() override;

protected:

	/* N�mero de frames de animaci�n */
	int m_numFrames;
	/* N�mero de frames/segundo */
	int m_animSpeed;
};


class AnimatedGraphicCreator : public BaseCreator
{
	GameObject* CreateGameObject() const override
	{
		return new AnimatedGraphic();
	}
};


#endif /* defined(__AnimatedGraphic__) */