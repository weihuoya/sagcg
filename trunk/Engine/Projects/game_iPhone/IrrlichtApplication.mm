/*
 *  Application.mm
 *  irrlichtApp iPhone Framework
 *
 */

#import "irrlichtAppDelegate.h"

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>

#include <sys/types.h>
#include <sys/sysctl.h>

#import <iostream>
#import "IrrlichtApplication.h"
#include "Application.h"
//#include "StdAfx.h"
#import "EAGLView.h"

extern "C++" IrrlichtDevice * getGlobalIrrlichtDevice();
extern "C++" int getDeviceWidth();
extern "C++" int getDeviceHeight();
//Global returnet 	IrrlichtDevice
IrrlichtDevice *device;
int g_DeviceWidth=0; 
int g_DeviceHeight=0;
extern "C" int GetPlatform();

//_irrlichtMain is the equivalent of the main in a normal main.cpp,
//do your normal irrlicht stuff below (rather use InitApplication)

int IrrlichtApplication::_irrlichtMain()
{
	//If initialising fails, quit early
	if(!InitApplication())
		return 1;
	return 0;
}


void IrrlichtApplication::_applicationWillUpdate()
{
	//This is the tick/update from the main application timer
	
	UpdateScene();
}
void IrrlichtApplication::_GameSWFWillUpdate()
{

}
void IrrlichtApplication::_applicationWillTerminate()
{
	//This notification comes from the system when the home/back button is pressed, 
	//So we want to shut down immediately because we will never get back into the main loop
	
	QuitApplication();
}

void IrrlichtApplication::_applicationWilldidRotate()
{
	//This notification is Rotate device
    if(getGlobalIrrlichtDevice())
    {
    getGlobalIrrlichtDevice()->getVideoDriver()->setViewPort(core::rect<s32>(0,0,getDeviceWidth(),getDeviceHeight()));
    }
}

void IrrlichtApplication::_applicationDidBecomeActive()
{
	//Respond to the application returning from a system event,
	//Such as unlocking the device after it has "fallen asleep"
	//This is also called when the application first becomes active,
	//so becareful that you dont run something thats uninitialised
}

void IrrlichtApplication::_applicationWillResignActive()
{
	//This is called when the application will enter a suspended
	//state, for example when the "lock" button is pressed.
}

bool IrrlichtApplication::InitApplication()
{
	//Create a copy of our application for use.
	irrlichtAppDelegate *appDelegate = (irrlichtAppDelegate*)[[UIApplication sharedApplication] delegate];
	int platform=PLATFORM_IPHONE_4;
    platform=GetPlatform();
	//Set up some creation parameters , normally what is below is fine
	SIrrlichtCreationParameters params;

	params.DriverType = video::EDT_OGLES1;

	switch (platform)
    {
        //320x480
        case PLATFORM_IPHONE_1G:
        case PLATFORM_IPHONE_3G:
        case PLATFORM_IPHONE_3GS:
        case PLATFORM_IPOD_1G:
        case PLATFORM_IPOD_2G:
        case PLATFORM_IPOD_3G:
        {
            g_DeviceHeight=320;
            g_DeviceWidth=480;
            break;
        }
       //640x960
        case PLATFORM_IPHONE_4:
        case PLATFORM_IPHONE_4S:
        case PLATFORM_IPHONE_UNKNOWN:
        case PLATFORM_IPOD_4G:
        case PLATFORM_IPOD_UNKNOWN:
        {
            /*g_DeviceHeight=640;
            g_DeviceWidth=960;*/
            g_DeviceHeight=320;
            g_DeviceWidth=480;
            break;
        }
        //764x1024        
        case PLATFORM_IPAD:
        case PLATFORM_IPAD2:
        {
            g_DeviceHeight=768;
            g_DeviceWidth=1024;
            break;
        }
        //1536x2048
        case PLATFORM_IPAD3:
        {
            /*g_DeviceHeight=1536;
            g_DeviceWidth=2048;*/
            g_DeviceHeight=768;
            g_DeviceWidth=1024;
            break;
        }
        default:
        {
            g_DeviceHeight=768;
            g_DeviceWidth=1024;
            break;
        }
    }
   	params.WindowSize = core::dimension2d<u32>(g_DeviceWidth,g_DeviceHeight);
	params.WindowId   = appDelegate.window;
	params.Bits		  = 24;
	
	device = createDeviceEx((const SIrrlichtCreationParameters)params);
	
	if(!device)
		return false;

	//The iPhone OS/Irrlicht Filesystem is out of sync, lets quickly fix that so we can load
	//our application resources as normal, as if it were a normal irrlicht filesystem
	
	device->getFileSystem()->changeWorkingDirectoryTo(getBundlePath().c_str());

	//Our application framework is ready, lets jump back into our game code
	Application::getInstance()->Run();
	return true;
}

bool IrrlichtApplication::QuitApplication()
{
	//The application is asking to quit,
	//Unload everything and quit the application
    Application::getInstance()->Quit();
	return true;
}

bool IrrlichtApplication::UpdateScene()
{
    Application::getInstance()->Update();
	return true;
}


core::stringc IrrlichtApplication::getBundlePath()
{
	CFBundleRef mainBundle  = CFBundleGetMainBundle();
	CFURLRef	mainURL		= CFBundleCopyBundleURL( mainBundle );
	
	//CFURLRef tempURL = CFURLCreateCopyDeletingLastPathComponent( NULL, mainURL );
	
	CFStringRef mainPath	= CFURLCopyFileSystemPath( mainURL, kCFURLPOSIXPathStyle );
	
	long		pathLength  = CFStringGetLength( mainPath ) + 1;
	char*		cStrPath	= new char[ pathLength ];
	CFStringGetCString( mainPath, cStrPath, pathLength, kCFStringEncodingMacRoman );
	
	//std::cout << "init_defaults::BundlePath = " << cStrPath << endl;
	
	core::stringc path( cStrPath );
	delete[ ] cStrPath;
	
	// CLEAN UP MEMORY
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