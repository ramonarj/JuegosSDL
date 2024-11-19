#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include "../../Kepri2D/GameState.h"
#include "../../Kepri2D/Level.h"
#include "../../Kepri2D/SDLGameObject.h"

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

	/* Nivel de tiles */
	Level* m_pLevel;

	/* Comprobación de colisiones entre 2 gameobjects */
	bool CheckCollision(SDLGameObject* p1, SDLGameObject* p2);
};


#endif /* defined(__PlayState__) */