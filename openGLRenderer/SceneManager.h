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
	void load(const char* scene);
	void update(glm::mat4 view, glm::mat4 projection, float deltaTime);
	void draw();
private:
	std::map<int, GameObject*> entities;
	std::map<int, Shader*> shaders;
	std::map<int, Model*> models;
};
