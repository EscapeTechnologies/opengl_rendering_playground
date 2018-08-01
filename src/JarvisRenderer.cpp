// Created By: Vineeth Yeevani
// Date: July 31, 2018
// Description: Rendering Engine

#include <iostream>
#include "JarvisRenderer.h"

JarvisRenderer::JarvisRenderer()
{
  std::cout << "Jarvis Renderer: Starting" << std::endl;
  std::cout << "Jarvis Renderer: Started" << std::endl;
}

void JarvisRenderer::run()
{
  std::cout << "Jarvis Renderer: Running" << std::endl;
}

void JarvisRenderer::staticRun()
{
  std::cout << "Jarvis Renderer: Static Run" << std::endl;

  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
}

void JarvisRenderer::close()
{
  std::cout << "Jarvis Renderer: Closing" << std::endl;
  std::cout << "Jarvis Renderer: Closed" << std::endl;
}
