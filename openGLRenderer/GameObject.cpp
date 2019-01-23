#include "GameObject.h"
#include <iostream>
#include <string>

using namespace std;

GameObject::GameObject(Shader *shader, Model *model, glm::vec3 position) :
	shader(*shader),
	model(*model)
{
	this->position = position;

	for (int i = 0; i < model->meshes.size(); i++)
	{
		AABB aabb;
		aabb.setBounds(model->meshes[0].vertices);
		this->bounds.push_back(aabb);
	}
}


GameObject::~GameObject()
{
}

void GameObject::update()
{

}

void GameObject::render()
{
	model.draw(shader);
}

glm::vec3 GameObject::getPosition()
{
	return this->position;
}

void GameObject::cleanUp()
{
	
}