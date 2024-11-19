#ifndef __PAUSESTATE__
#define __PAUSESTATE__

#include "Kepri2D.h"

class PauseState : public MenuState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool OnEnter();

	// Lo hereda de MenuState
	virtual void SetCallbacks(const std::vector<Callback>& callbacks);

	virtual std::string GetStateID() const { return s_PauseID; }

private:
	static const std::string s_PauseID;

	/* Callbacks para los botones (deben ser estáticas) */
	static void s_resumePlay();
	static void s_pauseToMenu();
};

#endif /* defined(__PauseState__) */