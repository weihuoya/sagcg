#include "StdAfx.h"
#include "Game/Game.h"
#include "GSMenu.h"
extern "C++" int getDeviceWidth();
extern "C++" int getDeviceHeight();


core::rect<s32>		GSMenu::translatePosition ( float Width, float Height, float sizeWidth, float sizeHeight )
{
	core::rect<s32>	tempPosition;
	float tempWidth=getDeviceWidth() /2;
	float tempHeight=getDeviceWidth() /2;
	tempPosition=core::rect<s32> ( ( tempWidth/1 ) *Width, ( tempHeight/1 ) *Height, ( tempWidth/1 ) *sizeWidth, ( tempHeight/1 ) *sizeHeight );
	return tempPosition;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSMenu::GSMenu()
{
	m_NewGameButton=0;
	m_LoadGameButton=0;
	m_AboutGameButton=0;
	m_Image=0;
	m_Imtex=0;
	Logs::debug ( "GSMenu\n" );
	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
	m_isEventManager->attach ( Events::IRRLICHT_EVENT, this );
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSMenu::~GSMenu()
{
	m_NewGameButton=0;
	m_LoadGameButton=0;
	m_AboutGameButton=0;
	m_Image=0;
	m_Imtex=0;
	Logs::debug ( "~GSMenu\n" );
	m_isEventManager->detach ( Events::IRRLICHT_EVENT, this );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State CTOR (when added to the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::ctor	( const StateMachine *sm )
{
	Logs::debug ( "State GSMenu::ctor\n" );
	//Beack ground
	//gfx/menu_2048x1536.png
	//gfx/menu_1024x768.png
	//gfx/menu_960x640.png
	/*m_Imtex=m_isGame->getVideoDriver()->getTexture ( "gfx/menu_1024x768.png" );
	m_Image = m_isGame->getGUIEnvironment()->addImage ( m_Imtex,
	          core::position2d<s32> ( 0, 0 ) );

	// lock the logo's edges to the bottom left corner of the screen
	m_Image->setAlignment ( EGUIA_UPPERLEFT, EGUIA_UPPERLEFT,
	                        EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT );
	*/
	//Button
	//(s32 id=-1, const wchar_t *text=0, const wchar_t *tooltiptext=0, video::ITexture *img=0, video::ITexture *pressedimg=0, bool isPushButton=false, bool useAlphaChannel=false
	core::rect<s32>	tempRect;
	float i=0.0;
	tempRect=translatePosition ( 0.6,0.05+i,0.95,0.1+i );
	m_NewGameButton = m_isGame->getGUIEnvironment()->addButton ( tempRect, 0, NEW_GAME_BUTTON,
	                  L"New Game", L"Launches a new Game" );
	i=i+0.06;
	tempRect=translatePosition ( 0.7,0.05+i,0.95,0.1+i );
	m_LoadGameButton = m_isGame->getGUIEnvironment()->addButton ( tempRect, 0, LOAD_GAME_BUTTON,
	                   L"Load game", L"Launches a Load game" );
	i=i+0.06;
	tempRect=translatePosition ( 0.8,0.05+i,0.95,0.1+i );
	m_AboutGameButton = m_isGame->getGUIEnvironment()->addButton ( tempRect, 0, ABOUT_GAME_BUTTON,
	                    L"About", L"Launches a About" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State DTOR (when removed from the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::dtor	( const StateMachine *sm )
{
	Logs::debug ( "State GSMenu::dtor\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State update (game update: update)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::update ( StateMachine *sm )
{
	Logs::debug ( "State GSMenu::update\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State pause (when a new state is added atop)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::pause	( const StateMachine *sm )
{
	Logs::debug ( "State GSMenu::pause\n" );
	m_NewGameButton->setVisible ( false );
	m_NewGameButton->setEnabled ( false );
	m_LoadGameButton->setVisible ( false );
	m_LoadGameButton->setEnabled ( false );
	m_AboutGameButton->setVisible ( false );
	m_AboutGameButton->setEnabled ( false );
	//m_Image->setVisible ( false );
	//m_Image->setEnabled ( false );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State resume (when the state above is removed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::resume	( const StateMachine *sm )
{
	Logs::debug ( "State GSMenu::resume\n" );
	m_NewGameButton->setVisible ( true );
	m_NewGameButton->setEnabled ( true );
	m_LoadGameButton->setVisible ( true );
	m_LoadGameButton->setEnabled ( true );
	m_AboutGameButton->setVisible ( true );
	m_AboutGameButton->setEnabled ( true );
	//m_Image->setVisible ( true );
	//m_Image->setEnabled ( true );
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw (game update: draw)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::draw	( const StateMachine *sm )
{
	Logs::debug ( "State GSMenu::draw\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw2d (draw 2d elements in front)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::draw2d	( const StateMachine *sm )
{
	Logs::debug ( "State GSMenu::draw2d\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State sleep (application is interrupted)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::sleep	( const StateMachine *sm )
{
	Logs::debug ( "State GSMenu::sleep\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State wakeup (application is resumed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSMenu::wakeup	( const StateMachine *sm )
{
	Logs::debug ( "State GSMenu::wakeup\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Update and Draw(draw2d) regardless of pause)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSMenu::isWorkingInParallel()
{
return true;
}
*/

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Loding screen Disable. )
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool GSMenu::isLoadingDisable()
{
	return true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EReceiver
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	GSMenu::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	Logs::debug ( "State GSMenu EEvent\n" );

	switch ( ev->getEventID() )
	{
		case Events::IRRLICHT_EVENT:
			handleEvIrrlichtEvents ( static_cast<const EvIrrlichtEvents *> ( ev ) );
			break;
	}
}
void	GSMenu::handleEvIrrlichtEvents ( const EvIrrlichtEvents *ev )
{
	if ( ev->irr_event.EventType==EET_GUI_EVENT && ev->irr_event.GUIEvent.EventType==EGET_BUTTON_CLICKED )
	{
		s32 id = ev->irr_event.GUIEvent.Caller->getID();

		switch ( id )
		{
			case NEW_GAME_BUTTON:
				Logs::info ( "NEW_GAME_BUTTON\n" );
				//m_isStateMachine->pushState<GSNewGame>();
				break;

			case LOAD_GAME_BUTTON:
				Logs::info ( "LOAD_GAME_BUTTON\n" );
				//m_isStateMachine->pushState<GSLoadGame>();
				break;

			case ABOUT_GAME_BUTTON:
				Logs::info ( "ABOUT_GAME_BUTTON\n" );
				break;
		}
	}
}


