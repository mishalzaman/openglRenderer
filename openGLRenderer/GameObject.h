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
	GameObject(Shader *shader, Model *model, glm::vec3 position, glm::vec3 scale);
	~GameObject();
	void update(glm::mat4 view, glm::mat4 projection, float deltaTime);
	void render();
	void cleanUp();
	glm::vec3 getPosition();
private:
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	std::vector<AABB*> bounds;
};

