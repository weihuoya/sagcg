#import <QuartzCore/QuartzCore.h>

#import "SaGCGViewController.h"
#import "EAGLView.h"

#import "SaGCGAppDelegate.h"
#import "EngineInit.h"

extern EngineInit *g_EngineInit;

@interface SaGCGViewController ()
@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) CADisplayLink *displayLink;
- (BOOL)loadShaders;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;
@end

@implementation SaGCGViewController

@synthesize animating, context, displayLink;

- (void)awakeFromNib
{
    EAGLContext *aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!aContext)
    {
        aContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    }
    
    if (!aContext)
        NSLog(@"Failed to create ES context");
    else if (![EAGLContext setCurrentContext:aContext])
        NSLog(@"Failed to set ES context current");
    
	self.context = aContext;
	[aContext release];
	
    [(EAGLView *)self.view setContext:context];
    [(EAGLView *)self.view setFramebuffer];
    
    if ([context API] == kEAGLRenderingAPIOpenGLES2)
        [self loadShaders];
   
   
    //add DeviceOrientationNotifications
    [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRotate:) name:@"UIDeviceOrientationDidChangeNotification" object:nil]; 
    
    animating = FALSE;
    animationFrameInterval = 1;
    self.displayLink = nil;
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
    [context release];
    
    [super dealloc];
}

- (void)viewWillAppear:(BOOL)animated
{
    [self startAnimation];
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self stopAnimation];
    
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload
{
	[super viewDidUnload];
	
    if (program)
    {
        glDeleteProgram(program);
        program = 0;
    }

    // Tear down context.
    if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	self.context = nil;	
}

- (void)didRotate:(NSNotification *)aNotification 
{
    g_EngineInit->Rotate();
	/*irrApp->_applicationWilldidRotate();
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
    NSLog(@"contentScaleFactor %f\n",SupperView.contentScaleFactor); // = 2.f;*/
    
}

- (NSInteger)animationFrameInterval
{
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1)
    {
        animationFrameInterval = frameInterval;
        
        if (animating)
        {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation
{
    if (!animating)
    {
        CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(drawFrame)];
        [aDisplayLink setFrameInterval:animationFrameInterval];
        [aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        self.displayLink = aDisplayLink;
        g_EngineInit->InitApplication();
        animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (animating)
    {
        [self.displayLink invalidate];
        self.displayLink = nil;
        animating = FALSE;
    }
}

- (void)drawFrame
{
    [(EAGLView *)self.view setFramebuffer];
    g_EngineInit->Update();
    [(EAGLView *)self.view presentFramebuffer];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file
{
    return TRUE;
}

- (BOOL)linkProgram:(GLuint)prog
{
    return TRUE;
}

- (BOOL)validateProgram:(GLuint)prog
{
    return TRUE;
}

- (BOOL)loadShaders
{
    return TRUE;
}

@end
