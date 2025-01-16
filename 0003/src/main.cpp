#include <iostream>
#include <memory>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

const char
	*vertex_shader_source = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0",

	*fragment_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
			"	FragColor = vec4(1.f, 0.5f, 0.2f, 1.f);\n"
		"}\n";

void init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0)
	{
		std::cerr << "SDL_Init: " << SDL_GetError() << '\n';
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

void init_glew()
{
	GLenum glew_status = glewInit();
	if(glew_status != GLEW_OK)
	{
		std::cerr << "glewInit: " << glewGetErrorString(glew_status) << '\n';
	}
}

void quit()
{
	SDL_Quit();
}

int main()
{
	init();

	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window(
		SDL_CreateWindow(
			"LearnOpenGL-Here",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			720, 480,
			SDL_WINDOW_OPENGL
		), SDL_DestroyWindow
	);

	bool is_running = !!window.get();

	SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
	SDL_GL_MakeCurrent(window.get(), gl_context);
	SDL_Event event;

	init_glew();

	float triangle_vertices[] =
	{
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.f, 0.5f, 0.f
	};

	unsigned int vertex_buffer_objet, vertex_shader, fragment_shader;
	
	glGenBuffers(1, &vertex_buffer_objet);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_objet);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	unsigned int shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);


	while(is_running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				is_running = false;
			}
		}
		glClearColor(0.3f, 0.3f, 0.3f, 1.f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_GL_SwapWindow(window.get());
	}

	SDL_GL_DeleteContext(gl_context);

	quit();

	return EXIT_SUCCESS;
}
