#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#define WINDOWPOS SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
#define WINDOWSIZE 720, 480

void init()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
	{
		std::cerr << SDL_GetError() << '\n';
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

void quit()
{
	SDL_Quit();
}

int main()
{
	init();

	SDL_WindowFlags window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window (
		SDL_CreateWindow(
			"LearnOpenGL", WINDOWPOS, WINDOWSIZE, window_flags
		),
		SDL_DestroyWindow
	);

	SDL_GLContext gl_context = SDL_GL_CreateContext(window.get());
	SDL_GL_MakeCurrent(window.get(), gl_context);
	SDL_Event event;

	bool is_running = !!window.get();

	while(is_running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				is_running = false;
			}
		}
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_GL_SwapWindow(window.get());
	}

	quit();
	return EXIT_SUCCESS;
}
