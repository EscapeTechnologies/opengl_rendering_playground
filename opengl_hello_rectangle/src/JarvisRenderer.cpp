// Created By: Vineeth Yeevani
// Date: July 31, 2018
// Description: Rendering Engine

#include <iostream>
#include "JarvisRenderer.h"

void drawTriangle();
int shaderProgram;
unsigned int VBO, VAO;
float vertices[] = {
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f,
  0.0f, 0.5f, 0.0f,
};

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
  drawTriangle();
}

void JarvisRenderer::close()
{
  std::cout << "Jarvis Renderer: Closing" << std::endl;
  std::cout << "Jarvis Renderer: Closed" << std::endl;
}

void compileShaders();

void drawTriangle()
{
  compileShaders();
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

// Create the shader programs and compile
void compileShaders()
{
  const char* vertexShaderSource ="#version 300 es\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
  const char* fragmentShaderSource = "#version 300 es\n"
    "precision mediump float;"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";
  // VERTEX SHADER
  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // Check if vertex shader successfully compiled
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "Jarvis Renderer: Vertex Shader Compile failed: " << std::endl << infoLog << std::endl;
  }

  // FRAGMENT SHADER
  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // Check if fragment shader successfully compiled
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "Jarvis Renderer: Fragment Shader Compile failed: " << std::endl << infoLog << std::endl;
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // Check if linking programs failed
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "Jarvis Renderer: Shader Program Compiler: " << std::endl << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}
