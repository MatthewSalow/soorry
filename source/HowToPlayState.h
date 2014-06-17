/***************************************************************
|	File:		HowToPlayState.h
|	Author:		Justin Mazzola
|	Course:		SGP
|	Purpose:	This state will show the player how to play with a slideshow
***************************************************************/

#pragma once

#include "IGameState.h"						// uses IGameState
#include "../SGD Wrappers/SGD_Handle.h"		// uses HTexture & HAudio
#include "../SGD Wrappers/SGD_Geometry.h"


/**************************************************************/
// Forward class declaration
//	- tells the compiler that the type exists
//	- allows us to create pointers or references
class Entity;
class EntityManager;
class MenuFlyweight;
class Button;
class BitmapFont;

#include "../SGD Wrappers/SGD_Declarations.h"

class HowToPlayState : public IGameState
{
public:
	/**********************************************************/
	// Singleton Accessor:
	static HowToPlayState* GetInstance(void);


	/**********************************************************/
	// IGameState Interface:
	virtual void	Enter(void)				override;	// load resources
	virtual void	Exit(void)				override;	// unload resources

	virtual bool	Input(void)				override;	// handle user input
	virtual void	Update(float elapsedTime)	override;	// update game entities / animations
	virtual void	Render(void)				override;	// render game entities / menus

private:

	/**********************************************************/
	// SINGLETON (not-dynamically allocated)
	HowToPlayState(void) = default;	// default constructor
	virtual ~HowToPlayState(void) = default;	// destructor

	HowToPlayState(const HowToPlayState&) = delete;	// copy constructor
	HowToPlayState& operator= (const HowToPlayState&) = delete;	// assignment operator


	MenuFlyweight* m_pMenuFlyweight;

	/**********************************************************/
	// Cursor Index
	int	m_nTab;

	/**********************************************************/
	// Textures
	SGD::HTexture m_hTutMain = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutTwo = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutThree = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutFour = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutFive = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutSix = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutSeven = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutEight = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutNine = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutNineB = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTut10 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTut11 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTut12 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTut13 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTut14 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTut15 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTut16 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutFinal = SGD::INVALID_HANDLE;

	/**********************************************************/
	// Audio
	SGD::HAudio	m_hTutorial = SGD::INVALID_HANDLE;
	SGD::HAudio	m_hTutorial2 = SGD::INVALID_HANDLE;
	SGD::HAudio	m_hTutorial3 = SGD::INVALID_HANDLE;
	SGD::HAudio	m_hTutorial4 = SGD::INVALID_HANDLE;
	SGD::HAudio	m_hTutorial5 = SGD::INVALID_HANDLE;
	SGD::HAudio	m_hTutorial6 = SGD::INVALID_HANDLE;
	SGD::HAudio	m_hTutorial7 = SGD::INVALID_HANDLE;
	SGD::HAudio m_hRock = SGD::INVALID_HANDLE;

	/**********************************************************/
	// Factory Methods
	Button* CreateButton() const;

	/**********************************************************/
	// Enumerations
	enum Tabs {
		TUT_MAIN, TUT_INTRO2, TUT_INTRO3, TUT_INTRO4, TUT_PICKUPS, TUT_ENEMIES,
		TUT_MOVEMENT, TUT_BUILD1, TUT_BUILD2, TUT_BUILD3, TUT_BUILD4,
		TUT_BUILD5, TUT_SHOP, TUT_TOWERS, TUT_SHOOTING, TUT_NADES, TUT_HEALING,
		TUT_THANKYOU, TABS_TOTAL};

	/**********************************************************/
	// Menu Items
	Button* m_pMainButton;
	BitmapFont* m_pFont;

	// ARCADE_MODE
	bool m_bTHEBOOL;
	bool m_bAccept;
	SGD::Vector m_vtStick;

};