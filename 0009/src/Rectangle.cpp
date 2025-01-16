#include "Rectangle.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL_image.h>

Rectangle::Rectangle(Shader &shader) noexcept
  : __position {0.f, 0.f}, __size {32.f, 32.f}, shader{shader}
{
  float vertices[] = 
  {
    0.f, 0.f, 0.f,  0.f, 0.f,
    1.f, 0.f, 0.f,  0.f, 1.f,
    1.f, 1.f, 0.f,  1.f, 1.f,
    0.f, 1.f, 0.f,  1.f, 0.f
  };
  GLuint indices[] =
  {
    0, 1, 3,
    1, 2, 3
  };

  glGenVertexArrays(1, &this->__vao);
  glGenBuffers(1, &this->__vbo);
  glGenBuffers(1, &this->__ebo);

  glBindVertexArray(this->__vao);

  glBindBuffer(GL_ARRAY_BUFFER, this->__vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->__ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (0));
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);


  glGenTextures(1, &this->__texture);
  glBindTexture(GL_TEXTURE_2D, this->__texture);

  SDL_Surface *img = IMG_Load("assets/brick.png");

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);

  SDL_FreeSurface(img);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  shader.use();
  glUniform1i(glGetUniformLocation(shader.getProgram(), "texture1"), 1);
}

void Rectangle::setPosition(glm::vec2 value) noexcept
{
  this->__position = value;
}
void Rectangle::setSize(glm::vec2 value) noexcept
{
  this->__size = value;
}
void Rectangle::draw() noexcept
{
  glm::mat4 ortho = glm::mat4(1.f), view = glm::mat4(1.f);

  ortho = glm::ortho(0.0f, 720.f, 480.f, 0.0f, -1.0f, 1.0f);
  view = glm::translate(view, glm::vec3(this->__position, 0.f));
  view = glm::scale(view, glm::vec3(this->__size, 0.f));



  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, this->__texture);

  shader.use();

  glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "projection"), 1, GL_FALSE, &ortho[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "view"), 1, GL_FALSE, &view[0][0]);
  
  glBindVertexArray(this->__vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

  glUseProgram(0);
}

Rectangle::~Rectangle() noexcept
{
  glDeleteVertexArrays(1, &this->__vao);
  glDeleteVertexArrays(1, &this->__ebo);
  glDeleteBuffers(1, &this->__vbo);
  glDeleteTextures(1, &this->__texture);
}