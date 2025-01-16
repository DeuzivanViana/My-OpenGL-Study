#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/glm.hpp>

#include "Shader.hpp"

class Rectangle
{
public:
  Rectangle(Shader&) noexcept;

  virtual void setPosition(glm::vec2) noexcept;
  virtual void setSize(glm::vec2) noexcept;
  virtual void draw() noexcept;

  virtual ~Rectangle() noexcept;
private:
  glm::vec2  __position, __size;
  GLuint __vao, __ebo, __vbo, __texture;
  Shader &shader;
};

#endif