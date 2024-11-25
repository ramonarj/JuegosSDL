#ifndef __CANVASOBJECT__
#define __CANVASOBJECT__

#include "GameObject.h"
#include "GameObjectFactory.h"

/* Clase perfectamente instanciable que se pinta sobre el canvas y no 
relativo a la cámara */
class CanvasObject : public GameObject
{
public:
	CanvasObject() : GameObject(){}
	virtual ~CanvasObject() {}

	virtual std::string Type() const override{ return "CanvasObject"; }

	void Draw() override;
};

class CanvasObjectCreator : public BaseCreator
{
	GameObject* CreateGameObject() const override
	{
		return new CanvasObject();
	}
};

#endif /* defined(__CanvasObject__) */