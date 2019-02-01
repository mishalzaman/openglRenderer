#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "GameObject.h"
#include "Shader.h"
#include "Model.h"

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void loadScene(const char* scene);
	void render(glm::mat4 view, glm::mat4 projection);
private:
	std::map<int, GameObject*> entities;
	std::map<int, Shader*> shaders;
	std::map<int, Model*> models;
};
