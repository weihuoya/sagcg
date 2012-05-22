// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Andrey Sidorov on 12.02.2012.
//  Copyright 2012 Andrey Sidorov. All rights reserved.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Application
//
//		The main (common) class handling the application/game
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Application.h"
#include "Game/GameState/GSBaseState.h"
#include "Game/Game.h"


Application *Application :: m_Application=NULL;
Application::Application()
{
	m_dt=0;
	m_minDeltaTime=1000/MAX_FPS;
	m_isStateMachine = & ( StateMachine::getInstance() );
	m_isEventManager = & ( EventManager::getInstance() );
	m_isGame = Game::getInstance();
}


void Application::Run()
{
	m_isStateMachine->pushState<GSBaseState>();
#ifdef WIN32

	while ( Update() )
	{
	}

	Quit();
#endif
}

bool Application::Update()
{
	if ( m_isGame->Run() !=1 )
	{
		//////////////////////////////////////
		//Update Deltatime and set Max FPS
		//////////////////////////////////////
		TimeManager::update_steptime();
		m_dt = TimeManager::get_steptime_ms();
#ifdef WIN32

		if ( m_dt<m_minDeltaTime )
		{
			TimeManager::sleep ( m_minDeltaTime-m_dt );
			m_dt=m_minDeltaTime;
		}

#endif
		//////////////////////////////////////
		//////////////////////////////////////
		m_isStateMachine->update ( m_dt );
		m_isEventManager->Update ( ( double ) m_dt );
		m_isGame->UIManagerUpdate ( ( float ) m_dt );
		return 1;
	}

	else
	{
		return 0;
	}
}


void Application::Quit()
{
	if ( m_isStateMachine )
	{
		while ( m_isStateMachine->stackSize() > 0 )
		{
			m_isStateMachine->popState();
		}
	}

	m_isGame->Quit();
	delete m_Application;
}