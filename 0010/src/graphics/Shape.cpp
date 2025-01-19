#include "graphics/Shape.hpp"


Shape::Shape() noexcept
{
}

void Shape::draw() noexcept
{
  glBindVertexArray(this->_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

Shape::~Shape() noexcept
{
  glDeleteVertexArrays(1, &this->_vao);
  glDeleteBuffers(1, &this->_vbo);
  glDeleteBuffers(1, &this->_ebo);
}