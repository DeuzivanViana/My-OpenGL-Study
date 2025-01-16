#include "core/Window.hpp"

Window::Window(const char *caption, glm::ivec2 size) noexcept
{
  this->create(caption, size);
}

void Window::create(const char *caption, glm::ivec2 size)
{
  this->__size = size;
  this->_createSDL_Window(caption);
}
void Window::clear(glm::vec3 color) const noexcept
{
  glClearColor(color.r, color.g, color.b, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::render() noexcept
{
  SDL_GL_SwapWindow(this->__window);
}
void Window::close() noexcept
{
  this->__is_open = false;
}

const bool& Window::isOpen() const noexcept
{
  return this->__is_open;
}

Window::~Window() noexcept
{
  SDL_GL_DeleteContext(this->__gl_context);
  SDL_DestroyWindow(this->__window);
}

void Window::_createSDL_Window(const char *caption) noexcept
{
  this->__is_open = (this->__window = SDL_CreateWindow(
    caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    this->__size.x, this->__size.y, SDL_WINDOW_OPENGL
  ));

  this->__gl_context = SDL_GL_CreateContext(this->__window);

  SDL_GL_MakeCurrent(this->__window, this->__gl_context);
}
