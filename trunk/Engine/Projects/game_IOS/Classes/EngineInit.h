#ifndef _EngineInit_H
#define _EngineInit_H

#import "Irrlicht.h"
#import "SaGCGAppDelegate.h"

class SaGCGAppDelegate;

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EngineInit
{
public:
	EngineInit();
    ~EngineInit();
    void Rotate();
    void Update();
	bool InitApplication();
    core::stringc getBundlePath();
	SaGCGAppDelegate *m_AppDelegate;
};

#endif //_EngineInit_H

