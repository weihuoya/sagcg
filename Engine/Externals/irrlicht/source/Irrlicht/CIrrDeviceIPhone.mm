// Copyright Redshift Software, Inc. 2008
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#import "CIrrDeviceIPhone.h"

#ifdef _IRR_COMPILE_WITH_IPHONE_DEVICE_

#import <UIKit/UIKit.h>
#import <QuartzCore/CAEAGLLayer.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/EAGL.h>
#import <stdio.h>


int g_IphoneCursorX=0;
int g_IphoneCursorY=0;
int g_IphoneScreenWidth=0;
int g_IphoneScreenHeight=0;
@interface IrrIPhoneView : UIView
{
	id dev;
}
//@property (nonatomic) id * dev;
- (void) setDevice:(id)device;
@end

@implementation IrrIPhoneView
+ (Class) layerClass
{
	return [CAEAGLLayer class];
}

- (BOOL) isMultipleTouchEnabled
{
	return YES;
}

- (void) setDevice:(id)device
{
	dev = device;
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	//NSLog(@">> IrrIPhoneView.touchBegan");

	UITouch *touch = [touches anyObject];
	CGPoint touchPoint = [touch locationInView:self];

	// event as mouse.
	irr::SEvent ev;
	ev.EventType = irr::EET_MOUSE_INPUT_EVENT;
	ev.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
	ev.MouseInput.X = touchPoint.x;
	ev.MouseInput.Y = touchPoint.y;
	//ev.MouseInput.Shift = 0;
	//ev.MouseInput.Control = 0;
	ev.MouseInput.ButtonStates = 0;	//MK_LBUTTON;
	//ev.MouseInput.Wheel = 0.f;
	[dev postEvent:&ev];


	// event as multi touch
	CGPoint nowTouchPoint, prevTouchPoint;
	ev.EventType = irr::EET_MULTI_TOUCH_EVENT;
	ev.MultiTouchInput.Event = irr::EMTIE_PRESSED_DOWN;
	ev.MultiTouchInput.clear();
	int idx = 0;
	for (touch in touches)
	{
		if (idx >= irr::NUMBER_OF_MULTI_TOUCHES) break;
		prevTouchPoint = [touch previousLocationInView:self];
		nowTouchPoint = [touch locationInView:self];
		ev.MultiTouchInput.Touched[idx] = 1;
		ev.MultiTouchInput.PrevX[idx] = prevTouchPoint.x;
		ev.MultiTouchInput.PrevY[idx] = prevTouchPoint.y;
		ev.MultiTouchInput.X[idx] = nowTouchPoint.x;
		ev.MultiTouchInput.Y[idx] = nowTouchPoint.y;
		idx ++;
	}
	[dev postEvent:&ev];
    irr::SEvent ev2;
    ev2.EventType = irr::EET_KEY_INPUT_EVENT;
    ev2.KeyInput.Key=irr::KEY_UP;
    ev2.KeyInput.PressedDown=true;
  	[dev postEvent:&ev2];
}

- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	//NSLog(@">> IrrIPhoneView.touchesMoved");

	UITouch *touch = [touches anyObject];
	CGPoint touchPoint = [touch locationInView:self];

	irr::SEvent ev;
	ev.EventType = irr::EET_MOUSE_INPUT_EVENT;
	ev.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
	ev.MouseInput.X = touchPoint.x;
	ev.MouseInput.Y = touchPoint.y;
    g_IphoneCursorX=touchPoint.x;
    g_IphoneCursorY=touchPoint.y;
	//ev.MouseInput.Shift = 0;
	//ev.MouseInput.Control = 0;
	ev.MouseInput.ButtonStates = 0;	//MK_LBUTTON;
	//ev.MouseInput.Wheel = 0.f;
	[dev postEvent:&ev];


	CGPoint nowTouchPoint, prevTouchPoint;
	ev.EventType = irr::EET_MULTI_TOUCH_EVENT;
	ev.MultiTouchInput.Event = irr::EMTIE_MOVED;
	ev.MultiTouchInput.clear();
	int idx = 0;
	for (touch in touches)
	{
		if (idx >= irr::NUMBER_OF_MULTI_TOUCHES) break;
		prevTouchPoint = [touch previousLocationInView:self];
		nowTouchPoint = [touch locationInView:self];
		ev.MultiTouchInput.Touched[idx] = 1;
		ev.MultiTouchInput.PrevX[idx] = prevTouchPoint.x;
		ev.MultiTouchInput.PrevY[idx] = prevTouchPoint.y;
		ev.MultiTouchInput.X[idx] = nowTouchPoint.x;
		ev.MultiTouchInput.Y[idx] = nowTouchPoint.y;
        if(idx==0)
        {
        g_IphoneCursorX=touchPoint.x;
        g_IphoneCursorY=touchPoint.y;
        }
		idx ++;
	}
	[dev postEvent:&ev];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	//NSLog(@">> IrrIPhoneView.touchesEnded");

	UITouch *touch = [touches anyObject];
	CGPoint touchPoint = [touch locationInView:self];

	irr::SEvent ev;
	ev.EventType = irr::EET_MOUSE_INPUT_EVENT;
	ev.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
	ev.MouseInput.X = touchPoint.x;
	ev.MouseInput.Y = touchPoint.y;
	//ev.MouseInput.Shift = 0;
	//ev.MouseInput.Control = 0;
	ev.MouseInput.ButtonStates = 0;	//MK_LBUTTON;
	//ev.MouseInput.Wheel = 0.f;
	[dev postEvent:&ev];


	CGPoint nowTouchPoint, prevTouchPoint;
	ev.EventType = irr::EET_MULTI_TOUCH_EVENT;
	ev.MultiTouchInput.Event = irr::EMTIE_LEFT_UP;
	ev.MultiTouchInput.clear();
	int idx = 0;
	for (touch in touches)
	{
		if (idx >= irr::NUMBER_OF_MULTI_TOUCHES) break;
		prevTouchPoint = [touch previousLocationInView:self];
		nowTouchPoint = [touch locationInView:self];
		ev.MultiTouchInput.Touched[idx] = 1;
		ev.MultiTouchInput.PrevX[idx] = prevTouchPoint.x;
		ev.MultiTouchInput.PrevY[idx] = prevTouchPoint.y;
		ev.MultiTouchInput.X[idx] = nowTouchPoint.x;
		ev.MultiTouchInput.Y[idx] = nowTouchPoint.y;
		idx ++;
	}
	[dev postEvent:&ev];
    
    irr::SEvent ev2;
    ev2.EventType = irr::EET_KEY_INPUT_EVENT;
    ev2.KeyInput.Key=irr::KEY_UP;
    ev2.KeyInput.PressedDown=false;
  	[dev postEvent:&ev2];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	NSLog(@">> IrrIPhoneView.touchesCancelled");

	UITouch *touch = [touches anyObject];
	CGPoint touchPoint = [touch locationInView:self];

	irr::SEvent ev;
	ev.EventType = irr::EET_MOUSE_INPUT_EVENT;
	ev.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
	ev.MouseInput.X = touchPoint.x;
	ev.MouseInput.Y = touchPoint.y;
	//ev.MouseInput.Shift = 0;
	//ev.MouseInput.Control = 0;
	ev.MouseInput.ButtonStates = 0;	//MK_LBUTTON;
	//ev.MouseInput.Wheel = 0.f;

	//[dev postEventFromUser:&ev];
}
@end

@interface IrrIPhoneDevice : NSObject <UIApplicationDelegate>
{
	@public
	
	EAGLContext * context;
	IrrIPhoneView * view;
	struct irr::MIrrIPhoneDevice * dev;
}
- (id) initWithDevice: (struct irr::MIrrIPhoneDevice*) device;
- (void) dealloc;
- (void) applicationWillResignActive: (UIApplication *) application;
- (void) applicationDidBecomeActive: (UIApplication *) application;
- (void) applicationWillTerminate: (UIApplication *) application;
- (void) displayCreateInWindow: (UIWindow**) window Width: (int) w Height: (int) h;
- (void) displayInitialize: (EAGLContext**) context_ View: (IrrIPhoneView**) view_;
- (void) displayBegin;
- (void) displayEnd;
- (void) postEvent: (irr::SEvent *) event;
@end

@implementation IrrIPhoneDevice
- (id) initWithDevice: (struct irr::MIrrIPhoneDevice*) device
{
	if ( (self = [super init]) )
	{
		context = nil;
		view = nil;
		dev = device;
	}
	return self;
}
- (void) dealloc
{
	[super dealloc];
}
- (void) applicationWillResignActive: (UIApplication *) application
{
	// Pause rendering.
	(*(dev->onWindowActive))(dev,0);
}
- (void) applicationDidBecomeActive: (UIApplication *) application
{
	// Resume after non-active pause of rendering.
	(*(dev->onWindowActive))(dev,1);
}
- (void) applicationWillTerminate: (UIApplication *) application
{
	(*(dev->onTerminate))(dev);
}
- (void) displayCreateInWindow: (UIWindow**) window Width: (int) w Height: (int) h
{
	// Create our view.
	CGRect rect;
	rect.origin.x = 0;
	rect.origin.y = 0;
	rect.size.width = w;
	rect.size.height = h;
    g_IphoneScreenWidth=w;
    g_IphoneScreenHeight=h;
    view = [[IrrIPhoneView alloc] initWithFrame: rect];
	view.layer.opaque = YES;
	if (nil != *window)
	{
		[(*window) addSubview: view];
	}
	
	// Create the GL context now, so that the driver initializetion
	// can make OpenGL calls.
	context = [[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES1];
	[EAGLContext setCurrentContext: context];
}
- (void) displayInitialize: (EAGLContext**) context_ View: (IrrIPhoneView**) view_
{
	*context_ = context;
	*view_ = view;
	[context renderbufferStorage: GL_RENDERBUFFER_OES fromDrawable: (CAEAGLLayer*)view.layer];
}
- (void) displayBegin
{
	if (context != [EAGLContext currentContext])
	{
		[EAGLContext setCurrentContext: context];
		[view setDevice:self];
	}
}
- (void) displayEnd
{
	if (context == [EAGLContext currentContext])
	{
		[context presentRenderbuffer: GL_RENDERBUFFER_OES];
	}
}
- (void) postEvent: (irr::SEvent *)  event
{
//NSLog(@">> IrrIPhoneDevice.postEvent");
	// Post event
	(*(dev->postEvent))(dev, event);
}
@end

void irr_device_iphone_display_create(struct irr::MIrrIPhoneDevice * dev,
	void** window, int w, int h)
{
	[((IrrIPhoneDevice*)dev->DeviceM) displayCreateInWindow: (UIWindow**)window Width: w Height: h];
}

void irr_device_iphone_display_init(struct irr::MIrrIPhoneDevice * dev,
	void** context, void** view)
{
	[((IrrIPhoneDevice*)dev->DeviceM) displayInitialize: (EAGLContext**)context View: (IrrIPhoneView**)view];
}

void irr_device_iphone_display_begin(struct irr::MIrrIPhoneDevice * dev)
{
	[((IrrIPhoneDevice*)dev->DeviceM) displayBegin];
}

void irr_device_iphone_display_end(struct irr::MIrrIPhoneDevice * dev)
{
	[((IrrIPhoneDevice*)dev->DeviceM) displayEnd];
}

void irr_device_iphone_create(struct irr::MIrrIPhoneDevice * dev)
{
	dev->DeviceM = [[IrrIPhoneDevice alloc] initWithDevice: dev];
	dev->displayCreate = &irr_device_iphone_display_create;
	dev->displayInit = &irr_device_iphone_display_init;
	dev->displayBegin = &irr_device_iphone_display_begin;
	dev->displayEnd = &irr_device_iphone_display_end;
}


extern "C++" int getIphoneCursorY()
{
    int cursor=g_IphoneCursorY;
   // NSLog(@">> IphoneCursorY %d\n",cursor);
    return cursor;
}

extern "C++" int getIphoneCursorX()
{
    int cursor=g_IphoneCursorX;
   // NSLog(@">> IphoneCursorX %d\n",cursor);
    return cursor;
}
#endif // _IRR_COMPILE_WITH_IPHONE_DEVICE_
