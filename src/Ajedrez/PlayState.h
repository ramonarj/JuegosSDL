#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include "GameState.h"
#include "Pieza.h"

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

	Pieza* piezaViva;
};


#endif /* defined(__PlayState__) */