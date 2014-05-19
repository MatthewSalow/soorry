/***************************************************************
|	File:		LoadingState.cpp
|	Author:		Justin Mazzola
|	Course:		SGP
|	Purpose:	The state where the player will be shown a 
|				"Loading.." screen to ensure the game hasnt frozen,
|				and have their data loaded to start gameplay
***************************************************************/
#include "LoadingState.h"

#include "Game.h"
#include "GameplayState.h"

#include "../SGD Wrappers/SGD_AudioManager.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"
#include "../SGD Wrappers/SGD_InputManager.h"
#include "../SGD Wrappers/SGD_String.h"

#include "../SGD Wrappers/SGD_EventManager.h"
#include "../SGD Wrappers/SGD_Event.h"
#include "../SGD Wrappers/SGD_MessageManager.h"
#include "../SGD Wrappers/SGD_Message.h"
#include "MessageID.h"

#include "BitmapFont.h"

#include "Entity.h"
#include "EntityManager.h"

#include <cstdlib>
#include <cassert>
#include <sstream>
using namespace std;


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cfloat>

/**************************************************************/
// GetInstance
//	- allocate static global instance
//	- return THE instance
/*static*/ LoadingState* LoadingState::GetInstance(void)
{
	static LoadingState s_Instance;	// stored in global memory once
	return &s_Instance;
}


/**************************************************************/
// Enter
//	- reset game
//	- load resources
//	- set up entities
/*virtual*/ void LoadingState::Enter(void)
{
	Game* pGame = Game::GetInstance();

	// Initialize the Event Manager
	m_pEvents = SGD::EventManager::GetInstance();
	m_pEvents->Initialize();

	// Initialize the Message Manager
	m_pMessages = SGD::MessageManager::GetInstance();
	m_pMessages->Initialize(&MessageProc);


	// Allocate the Entity Manager
	m_pEntities = new EntityManager;


	// Load Textures
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();


	// Load Audio
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();


	// Set background color
	SGD::GraphicsManager::GetInstance()->SetClearColor({ 0, 0, 0 });	// black
}


/**************************************************************/
// Exit
//	- deallocate entities
//	- unload resources
/*virtual*/ void LoadingState::Exit(void)
{
	// Release textures
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();


	// Release audio
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();


	// Deallocate the Entity Manager
	m_pEntities->RemoveAll();
	delete m_pEntities;
	m_pEntities = nullptr;


	m_pMessages->Terminate();
	m_pMessages = nullptr;
	SGD::MessageManager::DeleteInstance();


	// Terminate & deallocate the SGD wrappers
	m_pEvents->Terminate();
	m_pEvents = nullptr;
	SGD::EventManager::DeleteInstance();

}


/**************************************************************/
// Input
//	- handle user input
/*virtual*/ bool LoadingState::Input(void)
{
	Game* pGame = Game::GetInstance();
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	// Press Escape to quit
	if (pInput->IsKeyPressed(SGD::Key::Escape) == true)
	{
		pGame->ChangeState(GameplayState::GetInstance());
	}

	return true;	// keep playing
}


/**************************************************************/
// Update
//	- update game entities
/*virtual*/ void LoadingState::Update(float elapsedTime)
{


	// Update the entities
	m_pEntities->UpdateAll(elapsedTime);


	// Process the events & messages
	m_pEvents->Update();
	m_pMessages->Update();


	// Check collisions
}


/**************************************************************/
// Render
//	- render the game entities
/*virtual*/ void LoadingState::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	// Render the background
	pGraphics->DrawString("Loading...", { 200, 200 }, { 255, 0, 255 });


	// Render the entities
	m_pEntities->RenderAll();
}


/**************************************************************/
// MessageProc
//	- process messages queued in the MessageManager
//	- STATIC METHOD
//		- does NOT have invoking object!!!
//		- must use singleton to access members
/*static*/ void LoadingState::MessageProc(const SGD::Message* pMsg)
{
	/* Show warning when a Message ID enumerator is not handled */
#pragma warning( push )
#pragma warning( 1 : 4061 )

	// What type of message?
	switch (pMsg->GetMessageID())
	{
	case MessageID::MSG_UNKNOWN:
	default:
		OutputDebugStringW(L"Game::MessageProc - unknown message id\n");
		break;
	}


	/* Restore previous warning levels */
#pragma warning( pop )

}


/**************************************************************/
// Factory Methods
