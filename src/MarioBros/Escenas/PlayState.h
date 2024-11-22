#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include "Kepri2D.h"

class PlayState : public GameState
{
public:
	PlayState() : m_pLevel(nullptr) {}

	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const { return s_playID; }

private:
	static const std::string s_playID;

	/* Nivel de tiles */
	Level* m_pLevel;

	/* Comprobación de colisiones entre 2 gameobjects */
	bool CheckCollision(GameObject* p1, GameObject* p2);
};


#endif /* defined(__PlayState__) */