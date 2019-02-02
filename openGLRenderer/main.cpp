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
#include "Engine.h"

Engine* engine = new Engine(1280, 720);

using namespace std;

int main(int argc, char *argv[])
{
	engine->initialize();

	engine->load();

	float deltaTime, lastTime = 0.0f;

	while (!engine->shutdown()) {
		float currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		engine->bufferUpdate();

		engine->update(deltaTime);

		engine->render();
	}

	engine->cleanUp();
	delete(engine);

	return 0;
}