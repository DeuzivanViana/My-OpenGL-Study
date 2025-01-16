#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

class Shader
{
public:
  Shader() noexcept = default;
  Shader(std::string, std::string) noexcept;
  
  virtual void use() const noexcept;

  virtual ~Shader() noexcept;

protected:
  virtual void _checkError(GLuint, std::string) noexcept;

private:
  GLuint __program_id, __vertex_id, __fragment_id;
};

#endif