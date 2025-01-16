#ifndef SDL_UTILS_HPP
#define SDL_UTILS_HPP

namespace SDL_Utils
{
  void initSDL_main() noexcept;
  void initSDL_image() noexcept;
  
  void init() noexcept;
  void quit() noexcept;

  void quitSDL_main() noexcept;
  void quitSDL_image() noexcept;
} // namespace SDL_Utils


#endif