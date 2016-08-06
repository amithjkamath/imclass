/*
    Copyright 2005-2016 Intel Corporation.  All Rights Reserved.

    The source code contained or described herein and all documents related
    to the source code ("Material") are owned by Intel Corporation or its
    suppliers or licensors.  Title to the Material remains with Intel
    Corporation or its suppliers and licensors.  The Material is protected
    by worldwide copyright laws and treaty provisions.  No part of the
    Material may be used, copied, reproduced, modified, published, uploaded,
    posted, transmitted, distributed, or disclosed in any way without
    Intel's prior express written permission.

    No license under any patent, copyright, trade secret or other
    intellectual property right is granted to or conferred upon you by
    disclosure or delivery of the Materials, either expressly, by
    implication, inducement, estoppel or otherwise.  Any license under such
    intellectual property rights must be express and approved by Intel in
    writing.
*/

#import "OpenGLView.h"
#import <OpenGL/gl.h>
#import "guiAppDelegate.h"

// defined in macvideo.cpp
extern char* window_title;
extern int cocoa_update;
extern int g_sizex, g_sizey;
extern unsigned int *g_pImg;
void on_mouse_func(int x, int y, int k);
void on_key_func(int x);

@implementation OpenGLView

@synthesize timer;

- (void) drawRect:(NSRect)start
{
    glWindowPos2i(0, (int)self.visibleRect.size.height);
    glPixelZoom( (float)self.visibleRect.size.width /(float)g_sizex,
                -(float)self.visibleRect.size.height/(float)g_sizey);
    glDrawPixels(g_sizex, g_sizey, GL_BGRA_EXT, GL_UNSIGNED_INT_8_8_8_8_REV, g_pImg);
    glFlush();

    timer = [NSTimer scheduledTimerWithTimeInterval:0.03 target:self selector:@selector(update_window) userInfo:nil repeats:YES];
}

-(void) update_window{
    if( cocoa_update ) [self setNeedsDisplay:YES]; // TODO also clear cocoa_update?
    if( window_title ) [_window setTitle:[NSString stringWithFormat:@"%s", window_title]];
}

-(void) keyDown:(NSEvent *)theEvent{
    on_key_func([theEvent.characters characterAtIndex:0]);
}

-(void) mouseDown:(NSEvent *)theEvent{
    // mouse event for seismic and fractal
    NSPoint point= theEvent.locationInWindow;
    const int x = (int)point.x;
    const int y = (int)point.y;
    NSRect rect = self.visibleRect;
    on_mouse_func(x*g_sizex/(int)rect.size.width,((int)rect.size.height-y)*g_sizey/(int)rect.size.height,1);
    [self setNeedsDisplay:YES];
}

- (BOOL) acceptsFirstResponder
{
    return YES;
}

- (void) rightMouseDown:(NSEvent *)theEvent
{
    return;
}

-(void) viewDidEndLiveResize
{
    NSRect rect = self.visibleRect;
    const int x=(int)rect.size.width;
    const int y=(int)rect.size.height;
    [_window setTitle:[NSString stringWithFormat:@"X=%d Y=%d", x,y]];
}

@end
