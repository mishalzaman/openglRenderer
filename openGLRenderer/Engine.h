#pragma once

#include <GL/glew.h>
#include <sdl/SDL.h>
#include <iostream>

class Engine
{
public:
	Engine(int screenWidth, int screenHeight);
	~Engine();
	bool initialize();
	void load();
	void update();
	void render();
	void cleanUp();
private:
	
	int screenWidth;
	int screenHeight;
	SDL_Event event;
	SDL_Window *window;
	SDL_GLContext context;
};

