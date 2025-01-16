#ifndef APP_HPP
#define APP_HPP

#include "core/Window.hpp"

#include <SDL2/SDL_events.h>

class App
{
public:
  App() noexcept;

  virtual void run() noexcept;

  virtual ~App() noexcept;
protected:
  virtual void _clear() noexcept;
  virtual void _setup() noexcept;
  virtual void _update() noexcept;
  virtual void _render() noexcept;

private:
  Window __window;
  SDL_Event __event;
};

#endif