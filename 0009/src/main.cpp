#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "Shader.hpp"
#include "Rectangle.hpp"

#include "SDL_Utils.hpp"
#include "OpenGL_Utils.hpp"

int main(int, char*[])
{
  SDL_Utils::init();
  OpenGL_Utils::setupSDL_GL_Attribute();


  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
    SDL_CreateWindow("Learn OpenGL 0009", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, 720, 480,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
    SDL_DestroyWindow
  );
  bool is_running = window.get();
  SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
  SDL_Event event;

  SDL_GL_MakeCurrent(window.get(), gl_context);
  OpenGL_Utils::initGLEW();

  Shader shader("shaders/default.vs", "shaders/default.fs");
  Rectangle rectangle(shader), rectangle1(shader);

  rectangle1.setPosition(glm::vec2(128.f, 128.f));
  rectangle.setSize(glm::vec2(128.f, 128.f));

  while(is_running)
  {
    while (SDL_PollEvent(&event)) 
    {
      if(event.type == SDL_QUIT)
      {
        is_running = false;
      }
    }
    glViewport(0, 0, 720, 480);
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rectangle.draw();
    rectangle1.draw();

    SDL_GL_SwapWindow(window.get());
  }

  SDL_GL_DeleteContext(gl_context);
  SDL_Utils::quit();

  return EXIT_SUCCESS;
}