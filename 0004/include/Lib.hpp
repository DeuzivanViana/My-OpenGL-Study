#ifndef LIB_HPP
#define LIB_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace Lib
{ // start

void startSDL()
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
  {
    std::cerr << "Error(SDL_Init): " << SDL_GetError() << '\n';
  }
}

void setupOpenGL_Attribute()
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void startGLEW()
{
  GLenum glew_status = glewInit();
  if(glew_status != GLEW_OK)
  {
    std::cerr << "Error(glewInit): " << glewGetErrorString(glew_status) << '\n';
  }
}


} // end


#endif