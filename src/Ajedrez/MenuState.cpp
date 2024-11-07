#include "MenuState.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";

void MenuState::Update()
{
	// nothing for now
}
void MenuState::Render()
{
	m_botonPlay->Draw();
	// nothing for now
}
bool MenuState::OnEnter()
{
	std::cout << "entering MenuState\n";

	LoaderParams* pPlayParams = new LoaderParams(250, 250, 250, 104, "playButton");
	m_botonPlay = new SDLGameObject(pPlayParams);

	return true;
}
bool MenuState::OnExit()
{
	std::cout << "exiting MenuState\n";
	return true;
}