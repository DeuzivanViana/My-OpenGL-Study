#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL_render.h>

#include <glm/glm.hpp>
#include <SDL2/SDL_opengl.h>

class Window
{
public:
  Window() noexcept = default;
  Window(const char*, glm::ivec2) noexcept;

  virtual void create(const char*, glm::ivec2);
  virtual void clear(glm::vec3 = glm::vec3(.3f)) const noexcept;
  virtual void render() noexcept;
  virtual void close() noexcept;

  const bool& isOpen() const noexcept;

  virtual ~Window() noexcept;
protected:
  virtual void _createSDL_Window(const char*) noexcept;

private:
  SDL_Window *__window;
  SDL_GLContext __gl_context;
  glm::ivec2 __size;

  bool __is_open;
};

#endif