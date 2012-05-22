//
//  irrlichtAppDelegate.m
//  irrlichtApp iPhone Framework
//

#import "irrlichtAppDelegate.h"
#import "EAGLView.h"
#include "IrrlichtApplication.h"


#include <CoreGraphics/CoreGraphics.h>
#include <CoreGraphics/CGAffineTransform.h>
#define OS_IOS
#define kFPS			120.0
#define kSpeed			10.0
#define degreesToRadian(x) (M_PI * (x) / 180.0)

static IrrlichtApplication *irrApp = new IrrlichtApplication();
bool g_AplicationActive=false;
extern "C++" int getDeviceWidth();
extern "C++" int getDeviceHeight();

@implementation irrlichtAppDelegate

@synthesize window;
@synthesize glView;

- (void)applicationDidFinishLaunching:(UIApplication *)application 
{
	//Start the render schedule
	[NSTimer scheduledTimerWithTimeInterval:(1.0 / kFPS) target:self selector:@selector(applicationWillUpdate) userInfo:nil repeats:YES];
	[NSTimer scheduledTimerWithTimeInterval:(1.0 / kFPS) target:self selector:@selector(GameSWFWillUpdate) userInfo:nil repeats:YES];
    // enable orientation notification
	[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRotate:) name:@"UIDeviceOrientationDidChangeNotification" object:nil]; 
    
	//Call our main function
	irrApp->_irrlichtMain();
    g_AplicationActive=true;
}

- (void) applicationWillUpdate
{
    if(g_AplicationActive)
    {
        g_AplicationActive=false;
        irrApp->_applicationWillUpdate();
        g_AplicationActive=true;
    }
}
- (void) GameSWFWillUpdate
{
    if(g_AplicationActive)
    {
        irrApp->_GameSWFWillUpdate();
    }
}
- (void)applicationWillResignActive:(UIApplication *)application 
{
    g_AplicationActive=false;
	irrApp->_applicationWillResignActive();
}

- (void)didRotate:(NSNotification *)aNotification 
{
	irrApp->_applicationWilldidRotate();
    UIDeviceOrientation deviceOrientation = [[UIDevice currentDevice] orientation];
    UIView * SupperView=[glView  superview];
    CGAffineTransform transform = CGAffineTransformIdentity; 
    CGPoint center;
    CGRect  bouns;
    bouns.origin.x=0;
    bouns.origin.y=0;
    SupperView.contentScaleFactor=1.0;
    bouns.size.width=getDeviceWidth()*SupperView.contentScaleFactor;
    bouns.size.height=getDeviceHeight()*SupperView.contentScaleFactor;
    
////////////////////    Landscape
    if(deviceOrientation==UIDeviceOrientationLandscapeRight)
    {
        transform = CGAffineTransformMakeRotation(degreesToRadian(270));
        [SupperView setTransform:transform];
        [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeRight];
        [SupperView setBounds:bouns];
      //  [SupperView setFrame:bouns];
    }
    else if(deviceOrientation==UIDeviceOrientationLandscapeLeft)
    {
        transform = CGAffineTransformMakeRotation(degreesToRadian(90));
        [SupperView setTransform:transform];
        [[UIApplication sharedApplication] setStatusBarOrientation:UIInterfaceOrientationLandscapeLeft];
        [SupperView setBounds:bouns];
       // [SupperView setFrame:bouns];
    }
    NSLog(@"contentScaleFactor %f\n",SupperView.contentScaleFactor); // = 2.f;

}

- (void)applicationDidBecomeActive:(UIApplication *)application 
{
    g_AplicationActive=true;
	irrApp->_applicationDidBecomeActive();
}

- (void)applicationWillTerminate:(UIApplication *)application 
{
    g_AplicationActive=false;
	irrApp->_applicationWillTerminate();
}

- (void)dealloc 
{
	[window release];
	[glView release];
	[super dealloc];
}

@end
