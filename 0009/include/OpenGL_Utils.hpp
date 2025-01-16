#ifndef OPENGL_UTILS_HPP
#define OPENGL_UTILS_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace OpenGL_Utils
{
  void initGLEW() noexcept;
  void setupSDL_GL_Attribute() noexcept;
} // namespace OpenGL_Utils


#endif