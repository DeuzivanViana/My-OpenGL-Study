#ifndef SDL_MANAGER_HPP
#define SDL_MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace SDL_Manager
{
  void init() noexcept;
  void quit() noexcept;
} // namespace SDL_Manager


#endif