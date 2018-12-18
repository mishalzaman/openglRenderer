#include <iostream>
#include <string>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"
#include "CameraFP.h"
#include "Player.h"

bool firstMouse = true;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
bool quit = false;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

using namespace std;

int main(int argc, char *argv[])
{
	SDL_Event event;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

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
	//SDL_SetRelativeMouseMode(SDL_TRUE);
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

	CameraFP *camera = new CameraFP(SCREEN_WIDTH, SCREEN_HEIGHT);
	Player *player = new Player();
	GameObject *ship = new GameObject("shader.vs", "shader.fs", "assets/ship/ship.obj");
	GameObject *ground = new GameObject("shader.vs", "shader.fs", "assets/ground/ground.obj");
	GameObject *block = new GameObject("shader.vs", "shader.fs", "assets/block/block.obj");

	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);

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

		// ship controls
		if (keystates[SDL_SCANCODE_A])
		{
			player->yawLeft(deltaTime);
		}
		if (keystates[SDL_SCANCODE_D])
		{
			player->yawRight(deltaTime);
		}
		if (keystates[SDL_SCANCODE_W])
		{
			player->accelerate(deltaTime);
		}
		if (keystates[SDL_SCANCODE_S])
		{
			player->reverse(deltaTime);
		}
		if (keystates[SDL_SCANCODE_O])
		{
			player->accelerate(deltaTime);
		}
		if (keystates[SDL_SCANCODE_P])
		{
			player->reverse(deltaTime);
		}
		// Camera controls
		if (keystates[SDL_SCANCODE_UP])
		{
			camera->forward(deltaTime);
		}
		if (keystates[SDL_SCANCODE_DOWN])
		{
			camera->backward(deltaTime);
		}
		if (keystates[SDL_SCANCODE_RIGHT])
		{
			camera->strafeRight(deltaTime);
		}
		if (keystates[SDL_SCANCODE_LEFT])
		{
			camera->strafeLeft(deltaTime);
		}


		// Poll shut down
		if (SDL_PollEvent(&event) )
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
			}
			if (event.type == SDL_MOUSEMOTION)
			{

				int x, y;
				SDL_GetMouseState(&x, &y);
				camera->mousePositionUpdate(deltaTime, x, y);
				
				SDL_WarpMouseInWindow(window, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f);
			}
		}
			
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		// ship
		glm::mat4 view = camera->getViewMatrix();
		glm::mat4 model;
		model = player->getModel(deltaTime);
		ship->shader.use();
		ship->shader.setMat4("projection", projection);
		ship->shader.setMat4("view", view);
		ship->shader.setMat4("model", model);
		ship->render();

		// ground
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));
		ground->shader.use();
		ground->shader.setMat4("projection", projection);
		ground->shader.setMat4("view", view);
		ground->shader.setMat4("model", model);
		ground->render();

		// block
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -2.0f));
		block->shader.use();
		block->shader.setMat4("projection", projection);
		block->shader.setMat4("view", view);
		block->shader.setMat4("model", model);
		block->render();

		SDL_GL_SwapWindow(window);

		// cout << "frame rate: " + to_string(deltaTime) + "ms" << endl;
	}

	ship->cleanUp();
	delete(ship);
	delete(camera);
	delete(player);
	delete(block);

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}