#include "Engine.h"
#include "CameraFP.h"
#include "Input.h"
#include "SceneManager.h"
#include "SkyBox.h"
#include "FrameBuffer.h"

using namespace std;

Engine::Engine(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->projection = glm::perspective(glm::radians(45.0f), (float)this->screenWidth / (float)this->screenHeight, 0.1f, 100.0f);

	this->initSDL();
	this->initWindow();
	this->initContext();
	this->initGlew();
	this->initGLAttributes();
	this->enableMouseCapture(true);
	this->enableMouseCursor(false);
	this->enableDepthTest();
	this->setMouseToCenter();

	glViewport(0, 0, this->screenWidth, this->screenHeight);
}

Engine::~Engine()
{
}

void Engine::initialize()
{
	this->camera = new CameraFP(this->screenWidth, this->screenHeight);
	this->input = new Input();
	this->sceneManager = new SceneManager(*this->camera);
	this->skybox = new SkyBox();
	this->framebuffer = new FrameBuffer(this->screenWidth, this->screenHeight);
}

void Engine::load()
{
	this->sceneManager->load("scene.txt", this->projection);
	this->skybox->load();
	this->framebuffer->load();
}

void Engine::update(float deltaTime)
{
	this->updateUserInput(deltaTime);
	this->view = this->camera->getViewMatrix();
	this->sceneManager->update(this->view, deltaTime);
}

void Engine::render()
{
	this->cullingOptions();

	this->framebuffer->firstPass();
	this->sceneManager->draw();
	this->skybox->draw(this->view, this->projection);

	this->framebuffer->secondPass();
	this->framebuffer->render();

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

void Engine::cullingOptions()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

bool Engine::shutdown()
{
	return this->quit;
}

void Engine::initSDL()
{
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
	}
}

void Engine::initWindow()
{
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
	}
}

void Engine::initContext()
{
	this->context = SDL_GL_CreateContext(this->window);
}

void Engine::initGlew()
{
	glewExperimental = GL_TRUE;
	glewInit();
}


void Engine::initGLAttributes()
{
	int SDL_GL_SetAttribute(SDL_GLattr attr, int value);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void Engine::enableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void Engine::enableMouseCapture(bool state)
{
	state ? SDL_CaptureMouse(SDL_TRUE) : SDL_CaptureMouse(SDL_FALSE);
}

void Engine::enableMouseCursor(bool state)
{
	state ? SDL_ShowCursor(1) : SDL_ShowCursor(0);
}

void Engine::setMouseToCenter()
{
	SDL_WarpMouseInWindow(this->window, this->screenWidth / 2.0f, this->screenHeight / 2.0f);
}

void Engine::cleanUp()
{
	delete(this->camera);
	delete(this->input);
	delete(this->sceneManager);
	delete(this->skybox);
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
