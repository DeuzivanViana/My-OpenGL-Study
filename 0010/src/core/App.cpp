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

  this->__rect.create({0.f, 0.f, 32.f, 32.f}, {0.2f, 0.8f, 1.f});

}
void App::_clear() noexcept
{
  this->__window.clear(glm::vec3(.15f));
}
void App::_update() noexcept
{
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    if(event.type == SDL_QUIT)
    {
      this->__window.close();
    }
  }
}
void App::_render() noexcept
{
  this->__rect.draw();

  Rectangle rect;

  rect.create(glm::vec4(54.f, 87.f, 32.f, 64.f));

  rect.draw();

  this->__window.render();
}