#include "utils/OpenGL_Manager.hpp"

#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

void OpenGL_Manager::initGlew() noexcept
{
  GLuint glew_status = glewInit();

  if(glew_status != GLEW_OK)
  {
    std::cerr << "OpenGL_Manager::ERROR::glewInit: " << glewGetErrorString(glew_status) << '\n';
  }
}
void OpenGL_Manager::quit() noexcept
{
}