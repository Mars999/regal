#include <X11/Xdefs.h>
#include <X11/Xutil.h>

typedef XID GLXDrawable;
#include <GL/Regal.h>
#include "render.h"
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <cstdio>

int main (int argc, char ** argv)
{
    Display *dpy = XOpenDisplay(0);

    PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = NULL;

    const char *extensions = glXQueryExtensionsString(dpy, DefaultScreen(dpy));
    printf("%s\n",extensions);

    static int visual_attribs[] =
    {
      GLX_RENDER_TYPE, GLX_RGBA_BIT,
      GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
      GLX_DOUBLEBUFFER, true,
      GLX_RED_SIZE, 1,
      GLX_GREEN_SIZE, 1,
      GLX_BLUE_SIZE, 1,
      None
    };

    printf("Getting framebuffer config.\n");
    int fbcount;
    GLXFBConfig *fbc = glXChooseFBConfig(dpy, DefaultScreen(dpy), visual_attribs, &fbcount);
    if (!fbc)
    {
      printf("Failed to retrieve a framebuffer config.\n");
      return 1;
    }

    printf("Getting XVisualInfo\n");
    XVisualInfo *vi = glXGetVisualFromFBConfig(dpy, fbc[0]);

    XSetWindowAttributes swa;
    printf("Creating colormap\n");
    swa.colormap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;

    printf("Creating window\n");
    int width = 500;
    int height = 500;
    Window win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel|CWColormap|CWEventMask, &swa);
    if (!win)
    {
      printf("Failed to create window\n");
      return 1;
    }

    printf("Mapping window\n");
    XMapWindow(dpy, win);

    // Create an oldstyle context first, to get the correct function pointer for glXCreateContextAttribsARB
    GLXContext ctx_old = glXCreateContext(dpy, vi, 0, GL_TRUE);
    glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
    printf("glxCreateContextAttribsARB %p\n",glXCreateContextAttribsARB);
    glXMakeCurrent(dpy, 0, 0);
    glXDestroyContext(dpy, ctx_old);

    if (glXCreateContextAttribsARB == NULL)
    {
      printf("glXCreateContextAttribsARB entry point not found. Aborting.\n");
      return false;
    }

    static int context_attribs[] =
    {
      GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
      GLX_CONTEXT_MINOR_VERSION_ARB, 0,
      None
    };

    printf("Creating context\n");
    GLXContext ctx = glXCreateContextAttribsARB(dpy, fbc[0], NULL, true, context_attribs);
    if (!ctx)
    {
      printf("Failed to create GL3 context.\n");
      return 1;
    }

    printf("Making context current.\n");
    glXMakeCurrent(dpy, win, ctx);

    reshape( width, height );
    for(int i = 0; i < 1000000; i++ ) {
       display( true );
       usleep( 16000 );
       glXSwapBuffers( dpy, win );
    }

    ctx = glXGetCurrentContext();
    glXMakeCurrent(dpy, 0, 0);
    glXDestroyContext(dpy, ctx);
}
