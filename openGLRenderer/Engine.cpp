#include "Engine.h"
#include "CameraFP.h"
#include "Input.h"
#include "SceneManager.h"

Engine::Engine(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	this->camera = new CameraFP(this->screenWidth, this->screenHeight);
	this->input = new Input();
	this->sceneManager = new SceneManager();
}

Engine::~Engine()
{
}

void Engine::load()
{
	this->sceneManager->loadScene("scene.txt");
}

void Engine::update(float deltaTime)
{
	this->updateUserInput(deltaTime);

	// update projection and view matrix
	this->projection = glm::perspective(glm::radians(45.0f), (float)this->screenWidth / (float)this->screenHeight, 0.1f, 100.0f);
	this->view = this->camera->getViewMatrix();
}

void Engine::render()
{
	this->sceneManager->render(this->view, this->projection);
	SDL_GL_SwapWindow(this->window);
}

void Engine::updateUserInput(float deltaTime)
{
	this->input->update(deltaTime);
	if (this->input->isForward()) { camera->forward(deltaTime); };
	if (this->input->isBackward()) { camera->backward(deltaTime); };
	if (this->input->isStrafeLeft()) { camera->strafeLeft(deltaTime); };
	if (this->input->isStrafeRight()) { camera->strafeRight(deltaTime); };
	if (this->input->isMouseMotion())
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		camera->mousePositionUpdate(deltaTime, x, y);
		SDL_WarpMouseInWindow(this->window, this->screenWidth / 2.0f, this->screenHeight / 2.0f);
	}
	if (this->input->isQuit()) { this->quit = true; }
}

void Engine::preProcess()
{
	this->resetBuffer();
	this->GLOptions();
}

void Engine::resetBuffer()
{
	glClearColor(0.0, 0.1, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::GLOptions()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

bool Engine::shutdown()
{
	return this->quit;
}

bool Engine::initialize()
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	// initialize ttf for font rendering
	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
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

	SDL_WarpMouseInWindow(this->window, this->screenWidth / 2.0f, this->screenHeight / 2.0f);

	return true;
}

void Engine::cleanUp()
{
	delete(this->camera);
	delete(this->input);
	delete(this->sceneManager);
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	TTF_Quit();
	SDL_Quit();
}
