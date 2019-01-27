#pragma once

#include <sdl/SDL.h>
#include <iostream>

class Input
{
public:
	Input();
	~Input();
	int mouseX;
	int mouseY;
	void update(float deltaTime);
	bool isForward();
	bool isBackward();
	bool isStrafeLeft();
	bool isStrafeRight();
	bool isQuit();
private:
	SDL_Event event;
	bool forward = false;
	bool backward = false;
	bool strafeRight = false;
	bool strafeLeft = false;
	bool quit = false;
};

