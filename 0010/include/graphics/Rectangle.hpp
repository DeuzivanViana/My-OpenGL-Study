#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "graphics/Shape.hpp"
#include "graphics/Shader.hpp"

class Rectangle : public Shape
{
public:
  Rectangle() noexcept;

  virtual void create(glm::vec4, glm::vec3 = glm::vec3(1.f)) noexcept;
  virtual void draw() noexcept;

  virtual ~Rectangle() noexcept;

private:
  glm::vec4 __rect;
  glm::vec3 __color;
};

#endif
