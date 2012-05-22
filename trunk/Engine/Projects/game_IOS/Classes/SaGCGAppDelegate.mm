#import "SaGCGAppDelegate.h"
#import "SaGCGViewController.h"
#import "EngineInit.h"

EngineInit *g_EngineInit=new EngineInit();

@implementation SaGCGAppDelegate

@synthesize window;
@synthesize viewController;

- (void)alloc
{
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window.rootViewController = self.viewController;
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    [self.viewController stopAnimation];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [self.viewController startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [self.viewController stopAnimation];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Handle any background procedures not related to animation here.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Handle any foreground procedures not related to animation here.
}

- (void)dealloc
{
    [viewController release];
    [window release];
    //[g_EngineInit relese];
    [super dealloc];
}

@end
