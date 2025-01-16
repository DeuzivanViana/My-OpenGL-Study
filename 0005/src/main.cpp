#include <iostream>
#include <memory>

#include <Library.hpp>

int main()
{
  std::string
    glsl_vertex_file = Library::loadFile("shaders/vertex.vert"),
    glsl_fragment_file = Library::loadFile("shaders/fragment.frag");

  const char
    *vertex_shader_source = glsl_vertex_file.c_str(),
    *fragment_shader_source = glsl_fragment_file.c_str();

  Library::initSDL();
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
    SDL_CreateWindow(
      "Learn OpenGL 0005", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      720, 480, SDL_WINDOW_OPENGL
    ), SDL_DestroyWindow
  );
  float square_vertices[] =
  {
    -0.5f, -0.5f, 1.f,     0.2f, 0.6f, 0.7f,
    0.5f, -0.5f, 1.f,      0.5f, 0.4f, 0.1f,
    0.5f, 0.5f, 1.f,       0.8f, 0.6f, 0.2f,
    -0.5f, 0.5f, 1.f,      0.1f, 0.8f, 0.8f
  };
  GLuint square_indices[] = 
  {
    0, 1, 3,
    1, 2, 3
  };


  SDL_Event event;
  bool is_running = window.get();
  GLuint vbo, vao, ebo, fragment_shader, vertex_shader, shader_program;
  
  SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
  SDL_GL_MakeCurrent(window.get(), gl_context);
  Library::initGLEW();
  
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferDataARB(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);


  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  shader_program = glCreateProgram();

  glAttachShader(shader_program, fragment_shader);
  glAttachShader(shader_program, vertex_shader);
  glLinkProgram(shader_program);
  
  glDeleteShader(shader_program);
  glDeleteShader(fragment_shader);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while(is_running)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        is_running = false;
      }
    }
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    SDL_GL_SwapWindow(window.get());
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  SDL_GL_DeleteContext(gl_context);

  Library::close();

  return EXIT_SUCCESS;
}