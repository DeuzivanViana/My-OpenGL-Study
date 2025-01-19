#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>

class Shader
{
public:
  Shader() noexcept;

  virtual void loadFromFiles(std::string, std::string) noexcept;
  virtual void use() noexcept;

  virtual void setInt(GLint, const char*) noexcept;
  virtual void setMat4(glm::mat4, const char*) noexcept;

  virtual ~Shader() noexcept;
protected:
  virtual void _createShaders() noexcept;
  virtual void _checkShaderError(GLuint) noexcept;
  virtual void _checkProgramError(GLuint) noexcept;

private:
  GLuint __program, __vertex, __fragment;
};

#endif