#ifndef _EAGLView_H
#define _EAGLView_H
#import <UIKit/UIKit.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#include <OpenGLES/EAGL.h>

@interface EAGLView : UIView
{
@private
    EAGLContext *context;

    GLint framebufferWidth;
    GLint framebufferHeight;
    GLuint defaultFramebuffer, colorRenderbuffer;
}

@property (nonatomic, retain) EAGLContext *context;

- (void)setFramebuffer;
- (BOOL)presentFramebuffer;

@end
#endif