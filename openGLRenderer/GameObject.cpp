#include "GameObject.h"
#include <iostream>
#include <string>

using namespace std;

GameObject::GameObject(Shader *shader, Model *model, glm::vec3 position, glm::vec3 scale) :
	shader(*shader),
	model(*model)
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