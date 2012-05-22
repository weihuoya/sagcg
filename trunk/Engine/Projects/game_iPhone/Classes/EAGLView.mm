//
//  EAGLView.m
//  irrlichtApp iPhone Framework
//

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import <iostream>
#import "EAGLView.h"
#include <sys/types.h>
#include <sys/sysctl.h>

#define USE_DEPTH_BUFFER 1

extern "C" int GetPlatform()
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
	size_t size;
	int platform = PLATFORM_UNKNOWN;
	//char machine[30];
	sysctlbyname("hw.machine", NULL, &size, NULL, 0);
	char *machine = new char[size];
	sysctlbyname("hw.machine", machine, &size, NULL, 0);
	if (!strcasecmp(machine, "iPhone1,1"))	platform = PLATFORM_IPHONE_1G;
	else if (!strcasecmp(machine, "iPhone1,2"))	platform = PLATFORM_IPHONE_3G;
	else if (!strcasecmp(machine, "iPhone2,1"))	platform = PLATFORM_IPHONE_3GS;
	else if (!strcasecmp(machine, "iPhone3,1"))	platform = PLATFORM_IPHONE_4;
	else if (!strcasecmp(machine, "iPhone3,2")) platform = PLATFORM_IPHONE_4;
	else if (!strcasecmp(machine, "iPhone3,3")) platform = PLATFORM_IPHONE_4;
	else if (!strcasecmp(machine, "iPhone4,1")) platform = PLATFORM_IPHONE_4S;//PLATFORM_IPHONE_4S;
	else if (!strcasecmp(machine, "iPhone4,2")) platform = PLATFORM_IPHONE_4S;//PLATFORM_IPHONE_4S;
	else if (!strncmp(machine, "iPhone", 6))	platform = PLATFORM_IPHONE_UNKNOWN;
    
	else if (!strcasecmp(machine, "iPod1,1"))	platform = PLATFORM_IPOD_1G;
	else if (!strcasecmp(machine, "iPod2,1"))	platform = PLATFORM_IPOD_2G;
	else if (!strcasecmp(machine, "iPod3,1"))	platform = PLATFORM_IPOD_3G;
	else if (!strcasecmp(machine, "iPod4,1"))	platform = PLATFORM_IPOD_4G;
	//Need to add ipodtouch 3g...
	else if (!strncmp(machine, "iPod", 4))	platform = PLATFORM_IPOD_UNKNOWN;
    //#ifdef TARGET_IPAD_ONLY
	//BLaporte: TODO: Test this on device... :P
	else if (!strcasecmp(machine, "iPad1,1")) platform = PLATFORM_IPAD;
	else if (!strcasecmp(machine, "iPad2,1")) platform = PLATFORM_IPAD2;
	else if (!strcasecmp(machine, "iPad2,2")) platform = PLATFORM_IPAD2;
	else if (!strcasecmp(machine, "iPad2,3")) platform = PLATFORM_IPAD2;
	else if (!strcasecmp(machine, "iPad2,4")) platform = PLATFORM_IPAD3;
    else if (!strcasecmp(machine, "iPad3,1")) platform = PLATFORM_IPAD3;
	else if (!strcasecmp(machine, "iPad3,2")) platform = PLATFORM_IPAD3;
	else if (!strncmp(machine, "iPad3", 5))	platform = PLATFORM_IPAD3;
	
	delete(machine);
	[pool release];
    
	return platform;
}


// A class extension to declare private methods
@interface EAGLView ()

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) NSTimer *animationTimer;

- (BOOL) createFramebuffer;
- (void) destroyFramebuffer;

@end


@implementation EAGLView

@synthesize context;
@synthesize animationTimer;
@synthesize animationInterval;


// You must implement this method
+ (Class)layerClass {
    return [CAEAGLLayer class];
}


//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder {
    
    if ((self = [super initWithCoder:coder])) {
            float currentScaleFactor = 1.0;
        if (GetPlatform() == PLATFORM_IPHONE_4 || GetPlatform() == PLATFORM_IPHONE_4S || GetPlatform() == PLATFORM_IPOD_4G ||
			GetPlatform() == PLATFORM_IPAD3)
		{
            currentScaleFactor = 1.0;
            self.contentScaleFactor = currentScaleFactor;
		}
        
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if (!context || ![EAGLContext setCurrentContext:context]) {
            [self release];
            return nil;
        }
        
        [self setMultipleTouchEnabled:YES];
        
    }
    return self;
}


- (void)drawView {
  

}


- (void)layoutSubviews {
    [EAGLContext setCurrentContext:context];
    [self destroyFramebuffer];
    [self createFramebuffer];
    [self drawView];
}


- (BOOL)createFramebuffer 
{
    
    glGenFramebuffersOES(1, &viewFramebuffer);
    glGenRenderbuffersOES(1, &viewRenderbuffer);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
    
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
    
    if (USE_DEPTH_BUFFER) {
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
    }
    
    if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    
    return YES;
}


- (void)destroyFramebuffer {
    
    glDeleteFramebuffersOES(1, &viewFramebuffer);
    viewFramebuffer = 0;
    glDeleteRenderbuffersOES(1, &viewRenderbuffer);
    viewRenderbuffer = 0;
    
    if(depthRenderbuffer) {
        glDeleteRenderbuffersOES(1, &depthRenderbuffer);
        depthRenderbuffer = 0;
    }
}

- (void)dealloc {
    
    [self stopAnimation];
    
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [context release];  
    [super dealloc];
}


#pragma mark -
#pragma mark === Touch handling  ===
#pragma mark

// Handles the start of a touch
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesBegan\n ");
	/*if (Application::GetInstance() && !g_nWelcomeScreenIsBloackToutch && !g_FreemiumIGPBloackToutch)
	{
  		for (UITouch *touch in touches) 
  		{
 			CGPoint iPoint = [touch locationInView:self];
  			CGPoint iPointLast = [touch previousLocationInView:self];
			Application::GetInstance()->ReadTouchScreen( TOUCHEVT_PRESS, iPoint.x * currentScaleFactor, iPoint.y * currentScaleFactor,
                                                        touch.timestamp, touch.tapCount,
                                                        iPointLast.x * currentScaleFactor, iPointLast.y * currentScaleFactor,
                                                        (long)touch );
  		}
  	}*/
}

// Handles the continuation of a touch.
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesMoved\n ");
	/*if (Application::GetInstance() && !g_nWelcomeScreenIsBloackToutch && !g_FreemiumIGPBloackToutch)
	{
  		for (UITouch *touch in touches) 
  		{
 			CGPoint iPoint = [touch locationInView:self];
  			CGPoint iPointLast = [touch previousLocationInView:self];
			Application::GetInstance()->ReadTouchScreen( TOUCHEVT_DRAG,  iPoint.x * currentScaleFactor, iPoint.y * currentScaleFactor,
                                                        touch.timestamp, touch.tapCount,
                                                        iPointLast.x * currentScaleFactor, iPointLast.y * currentScaleFactor,
                                                        (long)touch );
  		}
  	}*/
}

// Handles the end of a touch event.
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touchesEnded\n ");
	/*if (Application::GetInstance()&& !g_nWelcomeScreenIsBloackToutch && !g_FreemiumIGPBloackToutch)
	{
  		for (UITouch *touch in touches) 
  		{
 			CGPoint iPoint = [touch locationInView:self];
  			CGPoint iPointLast = [touch previousLocationInView:self];
			Application::GetInstance()->ReadTouchScreen( TOUCHEVT_RELEASE, iPoint.x * currentScaleFactor, iPoint.y * currentScaleFactor,
                                                        touch.timestamp, touch.tapCount,
                                                        iPointLast.x * currentScaleFactor, iPointLast.y * currentScaleFactor,
                                                        (long)touch );
  		}
  	}*/
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{	
    NSLog(@"touchesCancelled\n ");
	/*if (Application::GetInstance() && !g_nWelcomeScreenIsBloackToutch && !g_FreemiumIGPBloackToutch)
	{
  		for (UITouch *touch in touches) 
  		{
 			CGPoint iPoint = [touch locationInView:self];
  			CGPoint iPointLast = [touch previousLocationInView:self];
			Application::GetInstance()->ReadTouchScreen( TOUCHEVT_RELEASE, iPoint.x * currentScaleFactor, iPoint.y * currentScaleFactor,
                                                        touch.timestamp, touch.tapCount,
                                                        iPointLast.x * currentScaleFactor, iPointLast.y * currentScaleFactor,
                                                        (long)touch );
  		}
  	}*/
}


@end
