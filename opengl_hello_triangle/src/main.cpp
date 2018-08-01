// Created By: Vineeth Yeevani
// Date: July 31, 2018
// Description: An OpenGL Extension loader test with GLEW

#include <X11/X.h>
#include <X11/Xlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <JarvisRenderer.h>
#include <thread>
#include <chrono>

using namespace std;

int main(int argc, char** argv)
{
  /* XLIB INIT */
  Display* dsp = XOpenDisplay(NULL);

  /* OPENGL INIT */
  GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
  XVisualInfo* vi = glXChooseVisual(dsp, 0, att);

  if (vi == NULL) {
    cout << "No appropriate Visual was found" << endl;
    return -1;
  }
  
  Colormap cmap = XCreateColormap(dsp, DefaultRootWindow(dsp), vi->visual, AllocNone);
  XSetWindowAttributes swa;
  swa.colormap = cmap;
  swa.event_mask = ExposureMask|KeyPressMask;

  // Find Root node screen size
  XWindowAttributes gwa;
  XGetWindowAttributes(dsp, DefaultRootWindow(dsp), &gwa); 
  
  Window win = XCreateWindow(dsp, DefaultRootWindow(dsp), 0, 0, gwa.width, gwa.height, 0, vi->depth, InputOutput, vi->visual, CWColormap|CWEventMask, &swa);

  Atom wm_state = XInternAtom(dsp, "_NET_WM_STATE", False);
  Atom fullscreen = XInternAtom(dsp, "_NET_WM_STATE_FULLSCREEN", False);

  /* SET XLIB SCREEN INFORMATION */
  XEvent xev;
  xev.type = ClientMessage;
  xev.xclient.window = win;
  xev.xclient.message_type = wm_state;
  xev.xclient.format = 32;
  xev.xclient.data.l[0] = 1;
  xev.xclient.data.l[1] = fullscreen;
  xev.xclient.data.l[2] = 0;

  XMapWindow(dsp, win);
  XSendEvent(dsp, DefaultRootWindow(dsp), False, SubstructureRedirectMask|SubstructureNotifyMask, &xev);
  GLXContext glc = glXCreateContext(dsp, vi, NULL, GL_TRUE);
  glXMakeCurrent(dsp, win, glc);

  //GLEW INIT
  GLenum err = glewInit(); 
  if (err != GLEW_OK) {
    cout << "GLEW INIT FAILED: " << glewGetErrorString(err) << endl;
    return 0;
  }

  glEnable(GL_DEPTH_TEST);
  XEvent loopXev;
  
  // Setup Graphics Context Size
  glViewport(0, 0, gwa.width, gwa.height);

  JarvisRenderer jr;
  
  // Wait for Exit command
  while(1) {
    XNextEvent(dsp, &loopXev); 
    if (loopXev.type == KeyPress) {
      // Destroy All Assets
      jr.close();
      glXMakeCurrent(dsp, None, NULL);
      glXDestroyContext(dsp, glc);
      XDestroyWindow(dsp, win);
      XCloseDisplay(dsp);
      return 0;
    }

    jr.staticRun();
    glXSwapBuffers(dsp, win);
  }
}
