//
//  Created by Andrey Sidorov on 12.02.2012.
//  Copyright 2012 Andrey Sidorov. All rights reserved.
//
#pragma once
#ifndef _STDAFX_H__
#define _STDAFX_H__

#pragma warning(disable: 4018) //'<' : signed/unsigned mismatch
#pragma warning(disable: 4244) //'argument' : conversion from 'int' to 'float', possible loss of data
#pragma warning(disable: 4101) //'' : unreferenced local variable

// Fedaultd and Setting
#include "Commons.h"

#if WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "Box2D.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gameswf.lib")
//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") // Console output OFF
#endif

#include <vector>
#include <list>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <math.h>

#ifdef GAMESWF
// ** GameSWF
#include	<gameswf/gameswf.h>
#include	<gameswf/gameswf_player.h>
#include	<gameswf/gameswf_root.h>
#include	<gameswf/gameswf_text.h>
#include	<gameswf/gameswf_dlist.h>
#include	<base/tu_file.h>

// ** Flash UI
class cUIManager;
class cUIObject;
class cUIText;

typedef gameswf::gc_ptr<gameswf::root>		tSwfRoot;
typedef gameswf::gc_ptr<gameswf::player>	tSwfPlayer;
typedef gameswf::render_handler			*tSwfRenderer;
typedef gameswf::character					*tSwfCharacter;
typedef tu_file							*tSwfFile;

typedef std::list< cUIObject * >			tUIObjectList;
#endif


// Other include
#include "Logs.h"
#include "TimeManager.h"
#include "Application.h"
#include "StateMachine.h"
#include "StateBase.h"
#include "EEventReceiver.h"
#include "EEvent.h"
#include "EventManager.h"
#include "StringManager.h"
#include "Managers/UIManager/UIManager.h"
//
#include "Game/Loading.h"
#include "Game/GameEvents/EvIrrlichtEvents.h"
#include "Game/GameEvents/EvGameSWFEvent.h"
//
#include "irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//
#ifdef BOX2D
#include "Box2D.h"
#endif
//#include "Game/Objects/GameObjects.h"

#endif