#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include "GameState.h"
#include "SDLGameObject.h"
#include <vector>

class PlayState : public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return s_playID; }

private:
	static const std::string s_playID;

	/* Lista de GameObjects */
	std::vector<GameObject*> m_gameObjects;

	/* Comprobación de colisiones entre 2 gameobjects */
	bool CheckCollision(SDLGameObject* p1, SDLGameObject* p2);
};


#endif /* defined(__PlayState__) */