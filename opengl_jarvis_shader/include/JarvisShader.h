// Created By: Vineeth Yeevani
// Date: July 31, 2018
// Description: Wrapper for easy Shader header

#ifndef JARVIS_SHADER_H
#define JARVIS_SHADER_H
#include "JarvisRenderer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
 public:
  // Program ID
  unsigned int ID;

  // Constructor reads and builds the shader
  Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

  // Use the shader
  void use();

  // Set Uniforms
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
};

#endif
