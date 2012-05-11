//
//  main.cpp
//  minimal_glut
//
//  Created by Cass Everitt on 2/1/12.
//  Copyright (c) 2012 n/a. All rights reserved.
//

#include <GL/Regal.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/RegalGLUT.h>
#endif

#include "render.h"

#include <cstdlib>

static void myDisplay()
{
  display(true);
  glutSwapBuffers();
}

static void myTick(int dummy)
{
	glutPostRedisplay();
	glutTimerFunc( 16, myTick, 0 );
}

static void myKeyboard(unsigned char c, int x, int y)
{
  switch (c)
  {
    case 'q':
    case 27:  /* Esc key */
      exit(0);
      break;
  }
}

int main(int argc, const char *argv[])
{
  glutInitDisplayString("rgba>=8 depth double");
  glutInitWindowSize(500, 500);
  glutInit( &argc, (char **) argv);
  glutCreateWindow("dreamtorus");

  // Regal workaround for OSX GLUT

  #ifdef __APPLE__
  RegalMakeCurrent(CGLGetCurrentContext());
  #endif

  glutTimerFunc(16, myTick, 0);
  glutDisplayFunc(myDisplay);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(myKeyboard);
  glutMainLoop();
  return 0;
}
