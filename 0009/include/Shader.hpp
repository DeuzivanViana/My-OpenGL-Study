#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>

class Shader
{
public:
  Shader() noexcept = default;
  Shader(std::string, std::string) noexcept;

  virtual void use() const noexcept;
  const GLuint &getProgram() const noexcept;

  virtual ~Shader() noexcept;
protected:
  virtual void _createShaderProgram() noexcept;
  virtual void _checkError(GLuint) noexcept;

private:
  GLuint __program, __vertex, __fragment;
};

#endif