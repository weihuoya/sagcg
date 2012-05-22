// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Andrey Sidorov on 12.02.2012.
//  Copyright 2012 Andrey Sidorov. All rights reserved.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GSBase
//
//		The This is the main Site(State) from which  the game will be all the bootstrap
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GAME_STATES_GSBase_H
#define GAME_STATES_GSBase_H

#include "StateBase.h"
#include "EEventReceiver.h"
class StateMachine;
class EventManager;
class Game;

class GSBase
	: public StateBase, public EEventReceiver
{

		friend class	StateMachine;

	private:

		GSBase();
	public:

		virtual			~GSBase();

		void	ctor		( const StateMachine *sm );	// when added to the StateMachine stack
		void	dtor		( const StateMachine *sm );	// when removed from the StateMachine stack

		void	update		( StateMachine *sm );

		void	pause		( const StateMachine *sm );	// when a new state is added atop
		void	resume		( const StateMachine *sm );	// when the state above is removed

		// External callbacks

		void	draw		( const StateMachine *sm );	// game update: draw
		void	draw2d		( const StateMachine *sm );	// draw 2d elements in front
		void	sleep		( const StateMachine *sm );	// application is interrupted
		void	wakeup		( const StateMachine *sm );	// application is resumed

		// Configuration state

		bool	isWorkingInParallel(); //If this option is true the state Update and Draw(draw2d) regardless of pause

		// EReceiver
		virtual void	onEvent ( const EEvent *ev, const EventManager *evMgr );

	private:

		StateMachine 		*m_isStateMachine;
		EventManager 		*m_isEventManager;
		Game 				*m_isGame;
};

#endif // GAME_STATES_GSBase_H
