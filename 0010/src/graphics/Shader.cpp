#include "graphics/Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader() noexcept
{
}

void Shader::loadFromFiles(std::string vertex_filepath, std::string fragment_filepath) noexcept
{
  this->_createShaders();

  // Vertex Shader
  std::ifstream file(vertex_filepath, std::ios::ate | std::ios::binary);
  std::streamsize file_size = file.tellg();
  char *buffer = new char[file_size + 1];

  file.seekg(0, std::ios::beg);
  file.read(buffer, file_size);
  buffer[file_size] = '\0';
  file.close();

  glShaderSource(this->__vertex, 1, &buffer, NULL);
  glCompileShader(this->__vertex);
  this->_checkShaderError(this->__vertex);

  delete[] buffer;

  // Fragment Shader
  file = std::ifstream(fragment_filepath, std::ios::ate | std::ios::binary);
  file_size = file.tellg();
  buffer = new char[file_size + 1];

  file.seekg(0, std::ios::beg);
  file.read(buffer, file_size);
  buffer[file_size] = '\0';
  file.close();

  glShaderSource(this->__fragment, 1, &buffer, NULL);
  glCompileShader(this->__fragment);
  this->_checkShaderError(this->__fragment);

  delete[] buffer;

  this->__program = glCreateProgram();
  glAttachShader(this->__program, this->__vertex);
  glAttachShader(this->__program, this->__fragment);
  glLinkProgram(this->__program);

  this->_checkProgramError(this->__program);

  glDeleteShader(this->__fragment);
  glDeleteShader(this->__vertex);
}
void Shader::use() noexcept
{
  glUseProgram(this->__program);
}
void Shader::setInt(GLint value, const char *name) noexcept
{
  GLint location = glGetUniformLocation(this->__program, name);
  glUniform1i(location, value);
}
void Shader::setMat4(glm::mat4 value, const char *name) noexcept
{
  GLint location = glGetUniformLocation(this->__program, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

Shader::~Shader() noexcept
{
  glDeleteProgram(this->__program);
}

void Shader::_createShaders() noexcept
{
  this->__vertex = glCreateShader(GL_VERTEX_SHADER);
  this->__fragment = glCreateShader(GL_FRAGMENT_SHADER);
}
void Shader::_checkShaderError(GLuint shader) noexcept
{
  GLint success;
  char buffer[1028];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(shader, 1028, NULL, buffer);
    std::cout << buffer << '\n';
  }
}
void Shader::_checkProgramError(GLuint program) noexcept
{
  GLint success;
  char buffer[1028];

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(program, 1028, NULL, buffer);
    std::cout << buffer << '\n';
  }
}
