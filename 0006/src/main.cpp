#include <iostream>
#include <memory>

#include "Shader.hpp"
#include "Utils.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

int main(int, char*[])
{
  Utils::initSDL();
  Utils::setupOpenGL_Attribute();

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
    SDL_CreateWindow("Learn OpenGL 0006", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
    SDL_DestroyWindow
  );
  SDL_Event event;
  SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
  SDL_GL_MakeCurrent(window.get(), gl_context);
  Utils::initGLEW();
  Shader shader("shaders/vertex.vs", "shaders/fragment.fs");
  bool is_running = window.get();
  GLuint vbo, vba, ebo, texture_id;
  SDL_Surface *image = IMG_Load("assets/brick.png");

  float triangle_vertices[] =
  {
    0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
  };
  GLuint tirangle_indices[] = 
  {
    0, 1, 3,
    1, 2, 3
  };

  glGenVertexArrays(1, &vba);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenTextures(1, &texture_id);

  glBindVertexArray(vba);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tirangle_indices), tirangle_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*) (sizeof(float) * 6));
  glEnableVertexAttribArray(2);

  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);

  SDL_FreeSurface(image);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  while (is_running)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        is_running = false;
      }
    }
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBindVertexArray(vba);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    
    SDL_GL_SwapWindow(window.get());
  }

  glDeleteTextures(1, &texture_id);

  SDL_GL_DeleteContext(gl_context);
  Utils::close();

  return EXIT_SUCCESS;
}