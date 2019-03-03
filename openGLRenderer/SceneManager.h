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
#include "CameraFP.h"

using namespace std;

class UniformBufferMatrices;
class UniformBufferLights;

class SceneManager
{
public:
	SceneManager(CameraFP &camera);
	~SceneManager();
	void load(const char* filename, glm::mat4 projection);
	void update(glm::mat4 view, float deltaTime);
	void draw();
	CameraFP &camera;
private:
	std::map<int, GameObject*> entities;
	std::map<int, GameObject*> lightEntities;
	std::map<int, GameObject*> materialEntities;
	std::map<int, Shader*> shaders;
	std::map<int, Model*> models;
	UniformBufferMatrices* uniformBuffersMatrices;
	UniformBufferLights* uniformBuffersLights;

	void loadSceneFile(const char* filename);
	std::map<int, GameObject*> &getEntities(std::string entity);
};
