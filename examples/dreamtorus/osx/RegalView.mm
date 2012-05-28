//
//  GlesView.mm
//  gles
//
//  Created by Cass Everitt on 3/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "RegalView.h"
#import "RGLOpenGLContext.h"
#include "render.h"
#include <stdio.h>



@implementation GlesView

bool resized = false;

NSTimer *timer = nil;

- (id)initWithCoder:(NSCoder *)aDecoder {

    [super initWithCoder: aDecoder];
  NSOpenGLPixelFormatAttribute attr[] = {
#if 0
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersionLegacy,
#else
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
#endif
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAAccelerated,
    NSOpenGLPFAAlphaSize, 8,
    NSOpenGLPFAColorSize, 32,
    NSOpenGLPFADepthSize, 24,
    NSOpenGLPFAStencilSize, 0,
    0
  };
  NSOpenGLPixelFormat *fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
    [self setPixelFormat: fmt];
    RGLOpenGLContext *rglCtx = [[RGLOpenGLContext alloc] initWithFormat:fmt shareContext:nil];
    [self setOpenGLContext: rglCtx];
    [rglCtx setView:self];
  timer = [NSTimer scheduledTimerWithTimeInterval:0.01 target:self selector:@selector (render) userInfo:nil repeats:YES];
    resized = false;
    return self;
}


- (void)drawRect:(NSRect)dirtyRect {
  if( resized == false ) {
    [self windowResized:NULL];
    resized = true;
  }
  display( true );
  [[self openGLContext] flushBuffer];
}

- (void) render {
  [self setNeedsDisplay:YES];
}

- (void)viewDidMoveToWindow
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(windowResized:) name:NSWindowDidResizeNotification
                                               object:[self window]];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [super dealloc];
}

- (void)windowResized:(NSNotification *)notification;
{
    NSRect rect = [[[self window] contentView] frame];
    NSRect crect = NSRectFromCGRect( CGRectMake( 0, 0, rect.size.width, rect.size.height ) );
    [self setFrame: crect];
    [self lockFocus];
    reshape( rect.size.width, rect.size.height );
    resized = true;
    [self unlockFocus];
}

@end
