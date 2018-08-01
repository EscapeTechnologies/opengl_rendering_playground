#ifndef JARVIS_RENDERER_H
#define JARVIS_RENDERER_H
#include <GL/glew.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "JarvisShader.h"

class JarvisRenderer
{
 public:
  JarvisRenderer();
  void staticRun();
  void run();
  void close();
};

#endif
