#include "Shader.hpp"

#include <fstream>

Shader::Shader(std::string vertex_filepath, std::string fragment_filepath) noexcept
{
  // Vertex Code
  std::ifstream file(vertex_filepath, std::ios::ate | std::ios::binary);
  std::streamsize file_size = file.tellg();
  char *code = new char[file_size + 1];

  file.seekg(0, std::ios::beg);
  file.read(code, file_size);
  code[file_size] = '\0';

  this->__vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(this->__vertex, 1, &code, NULL);
  glCompileShader(this->__vertex);
  this->_checkError(this->__vertex);

  delete[] code;
  file.close();

  // Fragment Code
  file = std::ifstream(fragment_filepath, std::ios::ate | std::ios::binary);
  file_size = file.tellg();
  code = new char[file_size + 1];

  file.seekg(0, std::ios::beg);
  file.read(code, file_size);
  code[file_size] = '\0';

  this->__fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(this->__fragment, 1, &code, NULL);
  glCompileShader(this->__fragment);
  this->_checkError(this->__fragment);

  delete[] code;
  file.close();

  this->_createShaderProgram();
}

void Shader::use() const noexcept
{
  glUseProgram(this->__program);
}
const GLuint &Shader::getProgram() const noexcept
{
  return this->__program;
}


Shader::~Shader() noexcept
{
  glDeleteProgram(this->__program);
}

void Shader::_createShaderProgram() noexcept
{
  this->__program = glCreateProgram();

  glAttachShader(this->__program, this->__vertex);
  glAttachShader(this->__program, this->__fragment);

  glLinkProgram(this->__program);

  glDeleteShader(this->__vertex);
  glDeleteShader(this->__fragment);
}
void Shader::_checkError(GLuint shader) noexcept
{
  GLint success;
  char buffer[1028];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(shader, 1028, NULL, buffer);
    std::cout << buffer;
  }
}