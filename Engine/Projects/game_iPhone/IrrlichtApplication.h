/*
 *  Application.h
 *  irrlichtApp iPhone Framework
 *
 */

#ifndef APPLCATION_H_
#define APPLCATION_H_

#import "Irrlicht.h"


using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;





class IrrlichtApplication
{
public:
	
	void _applicationWillResignActive();
	void _applicationDidBecomeActive();
	void _applicationWillUpdate();
    void _GameSWFWillUpdate();
	void _applicationWillTerminate();
    void _applicationWilldidRotate();    
	
	int  _irrlichtMain();
	
	bool InitApplication();
	bool QuitApplication();
	bool UpdateScene();
	
	core::stringc getBundlePath();
	
};



#endif APPLCATION_H_

