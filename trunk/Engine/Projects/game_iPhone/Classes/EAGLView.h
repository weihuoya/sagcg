//
//  EAGLView.h
//  irrlichtApp iPhone Framework
//



#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

//-----------------------------------------------------------
//		Device Type
//-----------------------------------------------------------
enum DeviceType
{
	PLATFORM_UNKNOWN = -1,
	PLATFORM_IPHONE_1G = 0,
	PLATFORM_IPHONE_3G,
	PLATFORM_IPHONE_3GS,
	PLATFORM_IPHONE_4,
    PLATFORM_IPHONE_UNKNOWN,
	PLATFORM_IPOD_1G,
	PLATFORM_IPOD_2G,
	PLATFORM_IPAD,
	PLATFORM_IPOD_3G,
	PLATFORM_IPOD_4G,
	PLATFORM_IPOD_UNKNOWN,
	PLATFORM_IPAD2,
	PLATFORM_IPAD3,
    PLATFORM_IPHONE_4S,
	PLATFORM_COUNT,
};
/*
This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
The view content is basically an EAGL surface you render your OpenGL scene into.
Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
*/
@interface EAGLView : UIView {
    
@private
    /* The pixel dimensions of the backbuffer */
    GLint backingWidth;
    GLint backingHeight;
    
    EAGLContext *context;
    
    /* OpenGL names for the renderbuffer and framebuffers used to render to this view */
    GLuint viewRenderbuffer, viewFramebuffer;
    
    /* OpenGL name for the depth buffer that is attached to viewFramebuffer, if it exists (0 if it does not exist) */
    GLuint depthRenderbuffer;
    
    NSTimer *animationTimer;
    NSTimeInterval animationInterval;
}

@property NSTimeInterval animationInterval;

- (void)startAnimation;
- (void)stopAnimation;
- (void)drawView;

@end
