#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include "GameState.h"
#include "GameObject.h"
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
};


#endif /* defined(__PlayState__) */