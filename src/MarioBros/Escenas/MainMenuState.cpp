#include "MainMenuState.h"

#include "PlayState.h"
#include <iostream>


const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::Update()
{
	// Update de todas las entidades
	for (GameObject* o : m_gameObjects)
		o->Update();
}
void MainMenuState::Render()
{
	for (GameObject* o : m_gameObjects)
		o->Draw();
}
bool MainMenuState::OnEnter()
{
	// Lectura del estado actual del XML
	StateParser stateParser;
	stateParser.ParseState("menu.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	// Añade los callbacks a la lista
	m_callbacks.push_back(0); 
	m_callbacks.push_back(s_menuToPlay);
	m_callbacks.push_back(s_exitFromMenu); //LEAK AQUI

	// Asigna los callbacks a los botones
	SetCallbacks(m_callbacks); 

	// Musica del menú
	SoundManager::Instance()->Load("clic.mp3", "clic", SOUND_SFX);
	SoundManager::Instance()->Load("Menu.mp3", "menu", SOUND_MUSIC);
	
	SoundManager::Instance()->PlayMusic("menu", -1);
	SoundManager::Instance()->ChangeVolume(50);
	//SoundManager::Instance()->PlaySound("clic", 0);

	// Prueba de texto
	Text* t = new Text();

	std::cout << "entering MenuState\n";
	return true;
}

void MainMenuState::s_menuToPlay()
{
	SoundManager::Instance()->PlaySound("clic", 0);
	SoundManager::Instance()->StopMusic();
	Game::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
	SoundManager::Instance()->PlaySound("clic", 0);
	Game::Instance()->DelayFor(500);
	Game::Instance()->Quit();
}

void MainMenuState::SetCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	if (!m_gameObjects.empty())
	{
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			// if they are of type MenuButton then assign a callback based on the id passed in from the file
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			if (pButton != nullptr) //duck typing
			{
				pButton->SetCallback(callbacks[pButton->GetCallbackID()]);
			}
		}
	}
}