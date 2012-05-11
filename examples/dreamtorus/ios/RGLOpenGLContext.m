#import "RGLOpenGLContext.h"


void RegalMakeCurrent( void * sysctx );

@implementation RGLOpenGLContext

+ (BOOL)setCurrentContext: (EAGLContext*) context
{
    BOOL res = [EAGLContext setCurrentContext: context];
    RegalMakeCurrent( (void *)context );
    return res;
}

@end
