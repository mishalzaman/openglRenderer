#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "GameObject.h"
#include "Shader.h"
#include "Model.h"
#include "UniformBuffer.h"

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void load(const char* filename, glm::mat4 projection);
	void update(glm::mat4 view, float deltaTime);
	void draw();
private:
	std::map<int, GameObject*> entities;
	std::map<int, Shader*> shaders;
	std::map<int, Model*> models;
	std::vector<UniformBuffer*> uniformBuffers;

	void loadSceneFile(const char* filename);
};
