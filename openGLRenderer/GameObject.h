#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include "AABB.h"
#include <vector>

class GameObject
{
public:
	Shader shader;
	Model model;
	GameObject(Shader *shader, Model *model, glm::vec3 position);
	~GameObject();
	void update();
	void render();
	void cleanUp();
	glm::vec3 getPosition();
private:
	glm::vec3 position;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	std::vector<AABB> bounds;
};

