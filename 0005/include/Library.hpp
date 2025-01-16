#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace Library
{
  
void initSDL() noexcept
{
  if(SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
  {
    std::cerr << "Error<SDL_Init>: " << SDL_GetError() << '\n';
  }
}
void initGLEW() noexcept
{
  GLuint glew_status = glewInit();
  if(glew_status != GLEW_OK)
  {
    std::cerr << glewGetErrorString(glew_status) << '\n';
  }
}
void setupOpenGL() noexcept
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
}

void close() noexcept
{
  SDL_Quit();
}

std::string loadFile(const char *filepath) noexcept
{
  std::ifstream file(filepath, std::ios::binary | std::ios::ate);
  std::streamsize file_size = file.tellg();
  char *buffer = new char[file_size + 1];

  file.seekg(0, std::ios::beg);
  file.read(buffer, file_size);
  buffer[file_size] = '\0';

  std::string content(buffer);

  delete[] buffer;
  return content;
}

} // namespace Library


#endif