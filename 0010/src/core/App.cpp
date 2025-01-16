#include "core/App.hpp"

#include "utils/SDL_Manager.hpp"
#include "utils/OpenGL_Manager.hpp"

App::App() noexcept
{
}

void App::run() noexcept
{
  this->_setup();
  while(this->__window.isOpen())
  {
    this->_update();
    this->_clear();
    this->_render();
  }
}

App::~App() noexcept
{
  SDL_Manager::quit();
  OpenGL_Manager::quit();
}

void App::_setup() noexcept
{
  SDL_Manager::init();

  this->__window.create("Learn OpenGL 0010", glm::ivec2(720, 480));

  OpenGL_Manager::initGlew();
}
void App::_clear() noexcept
{
  this->__window.clear(glm::vec3(.15f));
}
void App::_update() noexcept
{
  while(SDL_PollEvent(&this->__event))
  {
    if(this->__event.type == SDL_QUIT)
    {
      this->__window.close();
    }
  }
}
void App::_render() noexcept
{
  this->__window.render();
}