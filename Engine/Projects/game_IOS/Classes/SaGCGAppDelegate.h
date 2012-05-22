#ifndef _ApplicationDelegate_H
#define _ApplicationDelegate_H

#import <UIKit/UIKit.h>

@class SaGCGViewController;

@interface SaGCGAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    SaGCGViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet SaGCGViewController *viewController;

@end
#endif
