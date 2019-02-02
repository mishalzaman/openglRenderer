#pragma once

#include <GL/glew.h>
#include <sdl/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class CameraFP;
class Input;
class SceneManager;

class Engine
{
public:
	Engine(int screenWidth, int screenHeight);
	~Engine();
	bool initialize();
	void load();
	void update(float deltaTime);
	void render();
	void bufferUpdate();
	void cleanUp();
	bool shutdown();
private:
	int screenWidth;
	int screenHeight;
	bool quit = false;
	glm::mat4 projection;
	glm::mat4 view;
	SDL_Window *window;
	SDL_GLContext context;
	SDL_Event event;
	CameraFP* camera;
	Input* input;
	SceneManager* sceneManager;
};

