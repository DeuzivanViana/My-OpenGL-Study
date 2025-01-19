#ifndef APP_HPP
#define APP_HPP

#include <SDL2/SDL_events.h>

#include "graphics/Rectangle.hpp"
#include "core/Window.hpp"

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
  Shader __shader;

  Rectangle __rect;
};

#endif