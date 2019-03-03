#include "GameObject.h"
#include <iostream>
#include <string>

using namespace std;

GameObject::GameObject(Shader *shader, Model *model, CameraFP &camera, glm::vec3 position, glm::vec3 scale) :
	shader(*shader),
	model(*model),
	camera(camera)
{
	this->position = position;
	this->scale = scale;
}


GameObject::~GameObject()
{
}

void GameObject::update(float deltaTime)
{
	this->modelMatrix = glm::translate(glm::mat4(1.0f), this->position);
	this->modelMatrix = glm::scale(this->modelMatrix, this->scale); 
}

void GameObject::render()
{
	this->shader.use();
	this->shader.setMat4("model", this->modelMatrix);

	if (this->type == "static")
	{
		this->shader.setVec3("viewPos", this->camera.getCameraPosition());
		// light properties
		this->shader.setVec3("light.position", glm::vec3(0.0, 5.0, 0.0));
		this->shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		this->shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		this->shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		// material properties
		this->shader.setFloat("material.shininess", 64.0f);
		this->shader.setInt("material.diffuse", 0);
		this->shader.setInt("material.specular", 1);
	}

	this->model.draw(this->shader);
}

glm::vec3 GameObject::getPosition()
{
	return this->position;
}

void GameObject::setType(std::string type)
{
	this->type = type;
}

std::string GameObject::getType()
{
	return this->type;
}

void GameObject::cleanUp()
{
	
}