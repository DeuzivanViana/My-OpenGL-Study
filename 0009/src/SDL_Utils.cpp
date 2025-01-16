#include "SDL_Utils.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void SDL_Utils::initSDL_main() noexcept
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
  {
    std::cerr << "Error::SDL_Init -> " << SDL_GetError() << '\n';
  }
}
void SDL_Utils::initSDL_image() noexcept
{
  if(IMG_Init(IMG_INIT_PNG) < 0)
  {
    std::cerr << "Error::IMG_Init -> " << IMG_GetError() << '\n';
  }
}

void SDL_Utils::init() noexcept
{
  SDL_Utils::initSDL_main();
  SDL_Utils::initSDL_image();
}
void SDL_Utils::quit() noexcept
{
  SDL_Utils::quitSDL_main();
  SDL_Utils::quitSDL_image();
}

void SDL_Utils::quitSDL_main() noexcept
{
  SDL_Quit();
}
void SDL_Utils::quitSDL_image() noexcept
{
  IMG_Quit();
}