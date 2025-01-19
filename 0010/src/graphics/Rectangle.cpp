#include "graphics/Rectangle.hpp"

#include <glm/gtc/matrix_transform.hpp>

Rectangle::Rectangle() noexcept
{
}

void Rectangle::create(glm::vec4 rect, glm::vec3 color) noexcept
{
  float vertices[] = 
  {
    1.f,  1.f, 0.0f,  color.r, color.g, color.b,
    1.f, 0.f, 0.0f,  color.r, color.g, color.b,
    0.f, 0.f, 0.0f, color.r, color.g, color.b,
    0.f,  1.f, 0.0f, color.r, color.g, color.b
  };
  GLuint indices[] =
  {
    0, 1, 3,
    1, 2, 3
  };

  this->__rect = rect;
  this->__color = color;

  this->_shader.loadFromFiles("shaders/default.vs", "shaders/default.fs");

  glGenVertexArrays(1, &this->_vao);
  glGenBuffers(1, &this->_ebo);
  glGenBuffers(1, &this->_vbo);

  glBindVertexArray(this->_vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (0));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Rectangle::draw() noexcept
{
  this->_shader.use();

  glm::mat4 proj = glm::ortho( 0.f, 720.f, 480.f, 0.f, -1.f, 1.f );
  proj = glm::translate(proj, glm::vec3(this->__rect.x, this->__rect.y, 0.f));
  proj = glm::scale(proj, glm::vec3(this->__rect.z, this->__rect.w, 0.f));

  this->_shader.setMat4(proj, "perspective");

  Shape::draw();

  glUseProgram(0);
  glBindVertexArray(0);
}

Rectangle::~Rectangle() noexcept
{
}