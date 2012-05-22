// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Andrey Sidorov on 12.02.2012.
//  Copyright 2012 Andrey Sidorov. All rights reserved.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Game
//
//		This object with the initialization of the various engines
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef Game_H
#define Game_H

namespace irr
{
	struct SEvent;
}

class StateMachine;
class EventManager;

enum LANGUAGE
{
    LANGUAGE_UNKNOWN = -1,
    LANGUAGE_EN = 0,
    LANGUAGE_FR = 1,
    LANGUAGE_DE = 2,
    LANGUAGE_SP = 3,
    LANGUAGE_IT = 4,
    LANGUAGE_JP = 5,
    LANGUAGE_RU = 6,
    LANGUAGE_KO = 7,
    LANGUAGE_CN = 8,
    LANGUAGE_BR = 9,
    LANGUAGE_COUNTER = 10
};

class Game:public IEventReceiver
{
	protected:
		static Game		*m_Game;
		Game();
		bool m_isGameRun;
		int					m_DrawNumToUpdate;
		StateMachine 		*m_isStateMachine;
		EventManager 		*m_isEventManager;
		////////////////////////////////////////
		IrrlichtDevice			*m_IrrlichtDevice;	// Irrlicht Device
		ISceneManager			*m_SceneManager;	// Scene Manager
		IVideoDriver			*m_VideoDriver;		// Video Driver
		IGUIEnvironment			*m_GUIEnvironment;  // Menu
		int						 m_lastFPS;
		gui::IGUIFont			*m_font;
		int						 m_language;
#ifdef GAMESWF
		cUIManager				*m_UIManager;
#endif
#ifdef BOX2D
		b2World					*m_my2DPhysicsWorld;// Box2d PhysicsWorld
#endif
		////////////////////////////////////////

	public:
		static  Game *getInstance()
		{
			if ( !m_Game )
			{
				m_Game = new Game();
			}

			return m_Game;
		}
		bool OnEvent ( const irr::SEvent &IrrlichtEvent );
		void GameSWFEvent ( const char *command, const char *args );
		bool Run();
		bool Init();
		void Quit();
		void UIManagerUpdate ( float deltatime );
		IrrlichtDevice *getIrrlichtDevice();
		IVideoDriver *getVideoDriver();
		ISceneManager *getSceneManager();
		IGUIEnvironment	*getGUIEnvironment();
#ifdef GAMESWF
		cUIManager *getUIManager();
#endif
		bool m_MouseButton;
		int m_MouseInputX;
		int m_MouseInputY;
#ifdef BOX2D
		b2World	*get2DPhysicsWorld();
#endif
		void	setLanguage ( int language );
		int		getLanguage();
		bool	getGameIsRun()
		{
			return m_isGameRun;
		}

};

#endif // Game_H
