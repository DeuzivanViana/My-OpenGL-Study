#include "OpenGL_Utils.hpp"

#include <iostream>

void OpenGL_Utils::initGLEW() noexcept
{
  GLuint glew_status = glewInit();
  if(glew_status != GLEW_OK)
  {
    std::cerr << "Error::glewInit -> " << glewGetErrorString(glew_status) << '\n';
  }
}
void OpenGL_Utils::setupSDL_GL_Attribute() noexcept
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}