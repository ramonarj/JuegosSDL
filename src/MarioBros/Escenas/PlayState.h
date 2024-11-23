#ifndef __PLAYSTATE__
#define __PLAYSTATE__

#include "Kepri2D.h"

class PlayState : public GameState
{
public:
	PlayState() {}

	virtual bool OnEnter();

	virtual std::string GetStateID() const { return s_playID; }

private:
	static const std::string s_playID;
};


#endif /* defined(__PlayState__) */