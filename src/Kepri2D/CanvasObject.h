#ifndef __CANVASOBJECT__
#define __CANVASOBJECT__

#include "GameObject.h"
#include "GameObjectFactory.h"

/* Clase perfectamente instanciable que se pinta sobre el canvas y no 
relativo a la c�mara */
class CanvasObject : public GameObject
{
public:
	CanvasObject() : GameObject(){}
	virtual ~CanvasObject() {}

	virtual std::string Type() const { return "CanvasObject"; }

	void Draw();
};

class CanvasObjectCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new CanvasObject();
	}
};

#endif /* defined(__CanvasObject__) */