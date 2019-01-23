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
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Engine.h"

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

	// ShaderManager
	ShaderManager* shaders = ShaderManager::getInstance();
	shaders->add("general", "shader.vs", "shader.fs");
	shaders->add("aabb", "aabb.vs", "aabb.fs");
	shaders->add("lamp", "lamp.vs", "lamp.fs");
	shaders->add("light_casted", "light_casted.vs", "light_casted.fs");

	// ModelManager
	ModelManager* models = ModelManager::getInstance();
	models->add("ship", "assets/ship/ship.obj");
	models->add("ground", "assets/ground/ground.obj");
	models->add("block", "assets/block2/Cube_obj.obj");
	models->add("cube", "assets/block/block.obj");
	models->add("walls", "assets/walls/walls.obj");

	CameraFP *camera = new CameraFP(SCREEN_WIDTH, SCREEN_HEIGHT);
	Player *player = new Player();
	GameObject *ship = new GameObject(&shaders->get("light_casted"), &models->get("ship"), player->getPosition());
	GameObject *ground = new GameObject(&shaders->get("light_casted"), &models->get("ground"), glm::vec3(0.0f, -2.5f, 0.0f));
	GameObject *block = new GameObject(&shaders->get("light_casted"), &models->get("block"), glm::vec3(-2.0f, 2.0f, -2.0f));
	GameObject *lamp = new GameObject(&shaders->get("lamp"), &models->get("cube"), glm::vec3(0.0f, 0.0f, 0.0f));
	GameObject *walls = new GameObject(&shaders->get("light_casted"), &models->get("walls"), glm::vec3(-2.0f, 2.0f, -2.0f));

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
		ship->shader.setVec3("lightPos", lamp->getPosition());
		ship->shader.setVec3("lightColor", glm::vec3(1.0f));
		ship->shader.setVec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));
		ship->render();

		// ground
		model = glm::mat4(1.0f);
		model = glm::translate(model, ground->getPosition());
		ground->shader.use();
		ground->shader.setMat4("projection", projection);
		ground->shader.setMat4("view", view);
		ground->shader.setMat4("model", model);
		ground->shader.setVec3("lightPos", lamp->getPosition());
		ground->shader.setVec3("lightColor", glm::vec3(1.0f));
		ground->shader.setVec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));
		ground->render();

		// block
		model = glm::mat4(1.0f);
		model = glm::translate(model, block->getPosition());
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		block->shader.use();
		block->shader.setMat4("projection", projection);
		block->shader.setMat4("view", view);
		block->shader.setMat4("model", model);
		block->shader.setVec3("lightPos", lamp->getPosition());
		block->shader.setVec3("lightColor", glm::vec3(1.0f));
		block->shader.setVec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));
		block->render();

		// walls
		model = glm::mat4(1.0f);
		model = glm::translate(model, walls->getPosition());
		// model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
		walls->shader.use();
		walls->shader.setMat4("projection", projection);
		walls->shader.setMat4("view", view);
		walls->shader.setMat4("model", model);
		walls->shader.setVec3("lightPos", lamp->getPosition());
		walls->shader.setVec3("lightColor", glm::vec3(1.0f));
		walls->shader.setVec3("objectColor", glm::vec3(0.5f, 0.5f, 0.5f));
		walls->render();

		// lamp
		model = glm::mat4(1.0f);
		model = glm::translate(model, lamp->getPosition());
		model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
		lamp->shader.use();
		lamp->shader.setMat4("projection", projection);
		lamp->shader.setMat4("view", view);
		lamp->shader.setMat4("model", model);
		lamp->render();

		SDL_GL_SwapWindow(window);
	}

	delete(ship);
	delete(camera);
	delete(player);
	delete(ground);
	delete(block);
	delete(walls);
	shaders->cleanUp();
	models->cleanUp();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}