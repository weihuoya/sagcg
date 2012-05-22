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
#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H



class StateMachine;
class EventManager;
class Game;
class Application
{
	protected:
		static Application		*m_Application;
		Application();

		StateMachine 		*m_isStateMachine;
		EventManager 		*m_isEventManager;
		Game 				*m_isGame;

		unsigned long		m_dt; // Delta time
		unsigned long		m_minDeltaTime; // 1000/MAX_FPS

	public:
		static  Application *getInstance()
		{
			if ( !m_Application )
			{
				m_Application = new Application();
			}

			return m_Application;
		}
		void Run();
		bool Update();
		void Quit();
};





#endif // CORE_APPLICATION_H
