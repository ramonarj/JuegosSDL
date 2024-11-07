#include "PlayState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";

void PlayState::Update()
{
	piezaViva->Update();
	// nothing for now
}

void PlayState::Render()
{
	piezaViva->Draw();
	// nothing for now
}

bool PlayState::OnEnter()
{
	std::cout << "entering PlayState\n";

	LoaderParams* pPiezaParams = new LoaderParams(350, 350, 46, 62, "piezas");
	piezaViva = new Pieza(pPiezaParams);

	return true;
}

bool PlayState::OnExit()
{
	std::cout << "exiting PlayState\n";
	return true;
}