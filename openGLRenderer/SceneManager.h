#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ShaderManager.h"

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void loadScene(const char* scene);
	ShaderManager* shaders = ShaderManager::getInstance();
private:
	
};
