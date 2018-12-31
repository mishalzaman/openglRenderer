#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include "AABB.h"

class GameObject
{
public:
	Shader shader;
	Model model;
	AABB aabb;
	GameObject(Shader *shader, Model *model, glm::vec3 position);
	~GameObject();
	void render();
	void cleanUp();
	glm::vec3 getPosition();
private:
	glm::vec3 position;
};

