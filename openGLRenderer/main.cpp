#include <iostream>
#include <string>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CameraFP.h"
#include "Player.h"
#include "Input.h"
#include "SceneManager.h"

bool firstMouse = true;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
bool quit = false;

using namespace std;

int main(int argc, char *argv[])
{
	SDL_Event event;

	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	// Create window
	SDL_Window *window = SDL_CreateWindow(
		"Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL
	);

	if (!window)
	{
		std::cout << "Unable to create window\n";
		return false;
	}

	// Create context
	SDL_GLContext context = SDL_GL_CreateContext(window);
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

	SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);


	CameraFP *camera = new CameraFP(SCREEN_WIDTH, SCREEN_HEIGHT);
	Input input = Input();

	//setup scene
	SceneManager* scene = new SceneManager();
	scene->loadScene("scene.txt");

	float deltaTime = 0.0f; 
	float lastTime = 0.0f; 

	while (!quit) {
		float currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// reset buffer
		glClearColor(0.0, 0.1, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		input.update(deltaTime);
		if (input.isForward()) { camera->forward(deltaTime); };
		if (input.isBackward()) { camera->backward(deltaTime); };
		if (input.isStrafeLeft()) { camera->strafeLeft(deltaTime); };
		if (input.isStrafeRight()) { camera->strafeRight(deltaTime); };
		if (input.isMouseMotion())
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			camera->mousePositionUpdate(deltaTime, x, y);
			SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
		}
		if (input.isQuit()) { quit = true; }
			
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();

		scene->render(view, projection);

		SDL_GL_SwapWindow(window);
	}

	delete(camera);
	delete(scene);

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}