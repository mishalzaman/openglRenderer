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

	for (int i = 0; i < model->meshes.size(); i++)
	{
		AABB* aabb = new AABB();
		aabb->setBounds(model->meshes[i].vertices);
		this->bounds.push_back(aabb);
	}
}


GameObject::~GameObject()
{
}

void GameObject::update(glm::mat4 view, glm::mat4 projection, float deltaTime)
{
	this->projectionMatrix = projection;
	this->viewMatrix = view;
	this->modelMatrix = glm::translate(glm::mat4(1.0f), this->position);
	this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
}

void GameObject::render()
{
	this->shader.use();
	this->shader.setMat4("projection", this->projectionMatrix);
	this->shader.setMat4("view", this->viewMatrix);
	this->shader.setMat4("model", this->modelMatrix);
	this->model.draw(this->shader);

	for (int i = 0; i < this->bounds.size(); i++)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		this->bounds[i]->render(this->projectionMatrix, this->viewMatrix, this->position, this->scale);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

glm::vec3 GameObject::getPosition()
{
	return this->position;
}

void GameObject::cleanUp()
{
	
}