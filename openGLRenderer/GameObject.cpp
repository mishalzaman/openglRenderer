#include "GameObject.h"
#include <iostream>
#include <string>

using namespace std;

GameObject::GameObject(Shader *shader, Model *model, glm::vec3 position) :
	shader(*shader),
	model(*model),
	aabb()
{
	this->position = position;
	// aabb.setBounds(model.meshes[0].vertices);
}


GameObject::~GameObject()
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