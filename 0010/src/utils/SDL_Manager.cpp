#include "utils/SDL_Manager.hpp"

#include <iostream>

void SDL_Manager::init() noexcept
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL_Manager::ERROR::SDL_Init: " << SDL_GetError() << '\n';
  }
  if(IMG_Init(IMG_INIT_PNG) < 0)
  {
    std::cerr << "SDL_Manager::ERROR::IMG_Init: " << IMG_GetError() << '\n';
  }
}

void SDL_Manager::quit() noexcept
{
  IMG_Quit();
  SDL_Quit();
}