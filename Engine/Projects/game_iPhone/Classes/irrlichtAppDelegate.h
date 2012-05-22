//
//  irrlichtAppDelegate.h
//  irrlichtApp iPhone Framework
//


#import <UIKit/UIKit.h>

@class EAGLView;

@interface irrlichtAppDelegate : NSObject <UIApplicationDelegate> 
{
    UIWindow *window;
    EAGLView *glView;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;

@end

