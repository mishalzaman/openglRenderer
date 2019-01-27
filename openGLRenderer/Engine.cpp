#include "Engine.h"



Engine::Engine(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

Engine::~Engine()
{
}

bool Engine::initialize()
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	// Create window
	this->window = SDL_CreateWindow(
		"Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->screenWidth,
		this->screenHeight,
		SDL_WINDOW_OPENGL
	);

	if (!this->window)
	{
		std::cout << "Unable to create window\n";
		return false;
	}

	// Create context
	this->context = SDL_GL_CreateContext(this->window);
	SDL_CaptureMouse(SDL_TRUE);
	SDL_ShowCursor(0);
	// SDL_SetWindowFullscreen(window, SDL_TRUE);

	// initialize glew
	glewExperimental = GL_TRUE;
	glewInit();

	// Set OpenGL attributes
	int SDL_GL_SetAttribute(SDL_GLattr attr, int value);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Engine::render()
{
	SDL_GL_SwapWindow(this->window);
}

void Engine::cleanUp()
{
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
