#ifndef GAME_STATES_GSNewGame_H
#define GAME_STATES_GSNewGame_H

#include "StateBase.h"
#include "EEventReceiver.h"

class StateMachine;
class EventManager;
class Game;
class cUIObject;

class GSNewGame
	: public StateBase, public EEventReceiver
{

		friend class	StateMachine;

	private:

		GSNewGame();

	public:

		virtual			~GSNewGame();
		const char 	*getStateName() const;		// Return StateName
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
		/*
				bool	isWorkingInParallel(); //If this option is true the state Update and Draw(draw2d) regardless of pause
		*/

		/*
				bool	isLoadingDisable(); //If this option is true the state Loding screen Disable.
		*/

		// EReceiver
		virtual void	onEvent ( const EEvent *ev, const EventManager *evMgr );


	private:

		StateMachine 		*m_isStateMachine;
		EventManager 		*m_isEventManager;
		Game 				*m_isGame;
	public:
		cUIObject			*m_UIObject;

};

#endif // GAME_STATES_GSNewGame_H
