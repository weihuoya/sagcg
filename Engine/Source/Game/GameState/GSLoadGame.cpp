#include "StdAfx.h"
#include "Game/Game.h"
#include "Managers/UIManager/UIObject.h"
#include "GSLoadGame.h"
#include "GSTested_State.h"

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StateName
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *GSLoadGame::getStateName() const
{
	return "GSLoadGame";
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSLoadGame::GSLoadGame()
{
	Logs::info ( "GSLoadGame\n" );
	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
	m_UIObject=0;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSLoadGame::~GSLoadGame()
{
	Logs::info ( "~GSLoadGame\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State CTOR (when added to the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::ctor	( const StateMachine *sm )
{
	Logs::info ( "State GSLoadGame::ctor\n" );
	m_isEventManager->attach ( Events::IRRLICHT_EVENT, this );
	m_isEventManager->attach ( Events::GAME_SWF_EVENT, this );
	//m_UIObject=m_isGame->getUIManager()->CreateUIObject ( "data/swf/GSLoadGame.swf" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State DTOR (when removed from the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::dtor	( const StateMachine *sm )
{
	Logs::info ( "State GSLoadGame::dtor\n" );
	m_isEventManager->detach ( Events::IRRLICHT_EVENT, this );
	m_isEventManager->detach ( Events::GAME_SWF_EVENT, this );

	if ( m_UIObject )
	{
		m_isGame->getUIManager()->ReleaseUIObject ( m_UIObject );
		m_UIObject=0;
	}
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State update (game update: update)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::update ( StateMachine *sm )
{
	Logs::debug ( "State GSLoadGame::update\n" );
	m_isStateMachine->loadState<GSTested_State>();
	m_isStateMachine->popState();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State pause (when a new state is added atop)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::pause	( const StateMachine *sm )
{
	Logs::info ( "State GSLoadGame::pause\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State resume (when the state above is removed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::resume	( const StateMachine *sm )
{
	Logs::info ( "State GSLoadGame::resume\n" );
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw (game update: draw)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::draw	( const StateMachine *sm )
{
	Logs::debug ( "State GSLoadGame::draw\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw2d (draw 2d elements in front)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::draw2d	( const StateMachine *sm )
{
	Logs::debug ( "State GSLoadGame::draw2d\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State sleep (application is interrupted)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::sleep	( const StateMachine *sm )
{
	Logs::info ( "State GSLoadGame::sleep\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State wakeup (application is resumed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSLoadGame::wakeup	( const StateMachine *sm )
{
	Logs::info ( "State GSLoadGame::wakeup\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Update and Draw(draw2d) regardless of pause)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSLoadGame::isWorkingInParallel()
{
return true;
}
*/

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Loding screen Disable. )
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSLoadGame::isLoadingDisable()
{
return true;
}
*/


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EReceiver
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	GSLoadGame::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	Logs::debug ( "State GSLoadGame onEvent\n" );

	switch ( ev->getEventID() )
	{
		case Events::IRRLICHT_EVENT:
			Logs::debug ( "IRRLICHT_EVENT onEvent\n" );
			break;

		case Events::GAME_SWF_EVENT:
			Logs::info ( "GAME_SWF_EVENT onEvent\n" );
			break;
	}
}


