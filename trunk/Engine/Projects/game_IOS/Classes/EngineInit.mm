#include <sys/types.h>
#include <sys/sysctl.h>
#import <iostream>

#import "EAGLView.h"
#import "SaGCGAppDelegate.h"
#import "SaGCGViewController.h"
#import "EngineInit.h"
#include "Application.h"

// Extern
extern "C++" IrrlichtDevice * getGlobalIrrlichtDevice();
extern "C++" int getDeviceWidth();
extern "C++" int getDeviceHeight();
extern "C" int GetPlatform();

// Global 
IrrlichtDevice *device;
int g_DeviceWidth=0; 
int g_DeviceHeight=0;

EngineInit::EngineInit()
{
m_AppDelegate=nil;
}

void EngineInit::Rotate()
{
    if(getGlobalIrrlichtDevice())
    {
    getGlobalIrrlichtDevice()->getVideoDriver()->setViewPort(core::rect<s32>(0,0,getDeviceWidth(),getDeviceHeight()));
    }
}
void EngineInit::Update()
{
    Application::getInstance()->Update();
}

bool EngineInit::InitApplication()
{
	//Set up some creation parameters , normally what is below is fine
	SIrrlichtCreationParameters params;
	m_AppDelegate = (SaGCGAppDelegate*)[[UIApplication sharedApplication] delegate];
	params.DriverType = video::EDT_OGLES1;
    g_DeviceHeight=768;
    g_DeviceWidth=1024;
   	params.WindowSize = core::dimension2d<u32>(g_DeviceWidth,g_DeviceHeight);
	params.WindowId   = m_AppDelegate.window;
	params.Bits		  = 24;
	
	device = createDeviceEx((const SIrrlichtCreationParameters)params);
	
	if(!device)
		return false;
	device->getFileSystem()->changeWorkingDirectoryTo(getBundlePath().c_str());
    
    //Our application framework is ready, lets jump back into our game code
	Application::getInstance()->Run();
	return true;
}

core::stringc EngineInit::getBundlePath()
{
	CFBundleRef mainBundle  = CFBundleGetMainBundle();
	CFURLRef	mainURL		= CFBundleCopyBundleURL( mainBundle );
	CFStringRef mainPath	= CFURLCopyFileSystemPath( mainURL, kCFURLPOSIXPathStyle );
	
	long		pathLength  = CFStringGetLength( mainPath ) + 1;
	char*		cStrPath	= new char[ pathLength ];
	CFStringGetCString( mainPath, cStrPath, pathLength, kCFStringEncodingMacRoman );
	core::stringc path( cStrPath );
	delete[ ] cStrPath;
	CFRelease( mainURL );
	CFRelease( mainPath );
	return path;
}

extern "C++" IrrlichtDevice * getGlobalIrrlichtDevice()
{
    return device;
}

extern "C++" int getDeviceWidth()
{
    return g_DeviceWidth;
}

extern "C++" int getDeviceHeight()
{
    return g_DeviceHeight;
}