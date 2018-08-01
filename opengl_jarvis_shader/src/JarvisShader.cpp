// Created By: Vineeth Yeevani
// Date: July 31, 2018
// Description: Wrapper for easy Shader src

#include "JarvisShader.h"

// Construct Shader from files
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  // No Exceptions
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // Attempt to open the files
  try
    {
      vShaderFile.open(vertexPath);
      fShaderFile.open(fragmentPath);
      std::stringstream vShaderStream, fShaderStream;

      // Read the buffers into the streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
     
      // Close files
      vShaderFile.close();
      fShaderFile.close();

      // Convert read streams into strings
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
    }
  catch (std::ifstream::failure e)
    {
      std::cout << "|Jarvis Shader| - Shader File Read Error: " << std::endl;
    }
  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();
  
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // Compile vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "|Jarvis Shader| - Vertex Compile Error: " << infoLog << std::endl;
  };

  // Compile fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "|Jarvis Shader| - Fragment Compile Error: " << infoLog << std::endl;
  };
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    std::cout << "|Jarvis Shader| - Shader Linking Error: " << infoLog << std::endl;
  }
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

// Enable the GPU to use the shader program
void Shader::use()
{
  glUseProgram(ID);
}

// Set a boolean uniform
void Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

// Set a integer uniform
void Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

// Set a floating point integer uniform
void Shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
