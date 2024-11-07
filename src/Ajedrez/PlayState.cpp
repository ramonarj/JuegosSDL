#include "PlayState.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"

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

	// Carga de recursos con TextureManager
	TextureManager::Instance()->Load("Piezas.png", "piezas", Game::Instance()->GetRenderer());

	// Los LoaderParams habrá que borrarlos también no???
	LoaderParams* pPiezaParams = new LoaderParams(350, 350, 46, 62, "piezas");
	piezaViva = new Pieza(pPiezaParams);

	return true;
}

bool PlayState::OnExit()
{
	std::cout << "exiting PlayState\n";

	delete piezaViva;
	piezaViva = nullptr;

	return true;
}