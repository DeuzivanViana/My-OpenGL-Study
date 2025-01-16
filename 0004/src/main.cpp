#include <iostream>
#include <memory>

#include "Lib.hpp"

const char
  *vertex_shader_source = 
    "#version 460 core\n"
    "layout (location = 0) in vec3 pos;\n"
    "void main()\n"
    "{\n"
    "  gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
    "}\0",
  *fragment_shader_source = 
    "#version 460 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "  color = vec4(1.f, 0.3f, 0.2f, 0.7f);\n"
    "}\0";

int main()
{
  Lib::startSDL();
  Lib::setupOpenGL_Attribute();

  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
    SDL_CreateWindow("LearnOpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
    SDL_DestroyWindow
  );
  float triangle_vertices[] =
  {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f 
  };
  GLuint indices[] =
  {
    0, 1, 3,
    1, 2, 3
  };

  bool is_running = window.get();
  SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
  SDL_GL_MakeCurrent(window.get(), gl_context);
  Lib::startGLEW();
  SDL_Event event;
  GLuint vertex_shader, fragment_shader, vbo, shader_program, vao, ebo;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);
  glEnableVertexAttribArray(0);
  
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  shader_program = glCreateProgram();

  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  while (is_running)
  {
    while (SDL_PollEvent(&event))  
    {
      if(event.type == SDL_QUIT)
      {
        is_running = false;
      }
    }
    glClearColor(0.15f, 0.15f, 0.15f, 1.f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window.get());
  }
  
  SDL_GL_DeleteContext(gl_context);
  SDL_Quit();
  
  return EXIT_SUCCESS;
}