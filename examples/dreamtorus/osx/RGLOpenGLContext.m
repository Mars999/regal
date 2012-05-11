#import "RGLOpenGLContext.h"


void RegalMakeCurrent( CGLContextObj ctxobj );

@implementation RGLOpenGLContext

-(void)makeCurrentContext {
    [super makeCurrentContext];
    RegalMakeCurrent( CGLGetCurrentContext() );
}

@end
