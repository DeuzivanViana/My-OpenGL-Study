#include "Utils.hpp"

#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Utils::initSDL() noexcept
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
  {
    std::cerr << "Utils::Error<SDL_Init>: " << SDL_GetError() << '\n';
  }
  if(IMG_Init(IMG_INIT_PNG) < 0)
  {
    std::cerr << "Utils::Error<IMG_Init>: " << IMG_GetError() << '\n';
  }
}

void Utils::initGLEW() noexcept
{
  GLuint glew_status = glewInit();
  if(glew_status != GLEW_OK)
  {
    std::cerr << "Utils::Error<glewInit>: " << glewGetErrorString(glew_status) << '\n';
  }
}

void Utils::setupOpenGL_Attribute() noexcept
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Utils::close() noexcept
{
  SDL_Quit();
}