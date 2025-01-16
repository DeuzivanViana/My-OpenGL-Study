#include "Shader.hpp"

Shader::Shader(std::string vertex_filepath, std::string fragment_filepath) noexcept
{
  std::ifstream
    vertex_file(vertex_filepath, std::ios::binary | std::ios::ate),
    fragment_file(fragment_filepath, std::ios::binary | std::ios::ate);


  std::streamsize
    vertex_file_size = vertex_file.tellg(),
    fragment_file_size = fragment_file.tellg();
 
  vertex_file.seekg(0, std::ios::beg);
  fragment_file.seekg(0, std::ios::beg);
  
  char
    *v_vertex_code = new char[vertex_file_size + 1],
    *v_fragment_code = new char[fragment_file_size + 1];

  vertex_file.read(v_vertex_code, vertex_file_size);
  fragment_file.read(v_fragment_code, fragment_file_size);
  
  v_vertex_code[vertex_file_size] = '\0';
  v_fragment_code[fragment_file_size] = '\0';

  vertex_file.close();
  fragment_file.close();

  this->__vertex_id = glCreateShader(GL_VERTEX_SHADER);
  this->__fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
  this->__program_id = glCreateProgram();

  glShaderSource(this->__vertex_id, 1, &v_vertex_code, NULL);
  glCompileShader(this->__vertex_id);
  this->_checkError(this->__vertex_id, "SHADER::VERTEX");

  glShaderSource(this->__fragment_id, 1, &v_fragment_code, NULL);
  glCompileShader(this->__fragment_id);
  this->_checkError(this->__fragment_id, "SHADER::FRAGMENT");

  glAttachShader(this->__program_id, this->__fragment_id);
  glAttachShader(this->__program_id, this->__vertex_id);
  glLinkProgram(this->__program_id);

  glDeleteShader(this->__fragment_id);
  glDeleteShader(this->__vertex_id);

  delete[] v_fragment_code;
  delete[] v_vertex_code;
}

void Shader::use() const noexcept
{
  glUseProgram(this->__program_id);
}

const GLuint& Shader::getProgramID() const noexcept
{
  return this->__program_id;
}


Shader::~Shader() noexcept
{
  glDeleteProgram(this->__program_id);
}

void Shader::_checkError(GLuint shader_id, std::string type) noexcept
{
  char message[1024];
  GLint status;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
  
  if(!status)
  {
    glGetShaderInfoLog(shader_id, 1024, NULL, message);
    std::cerr << type << ": " << message << '\n';
  }
}
