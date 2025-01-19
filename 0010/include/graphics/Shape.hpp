#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "graphics/Shader.hpp"
#include <glm/glm.hpp>

class Shape
{
public:
  Shape() noexcept;

  virtual void draw() noexcept;

  virtual ~Shape() noexcept;
protected:
  Shader _shader;
  GLuint _vbo, _vao, _ebo;

private:
  glm::mat4 __model;
};

#endif