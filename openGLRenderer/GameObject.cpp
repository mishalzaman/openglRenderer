#include "GameObject.h"



GameObject::GameObject(const char* vertexPath, const char* fragmentPath, const char *filename) :
	shader(vertexPath, fragmentPath),
	model(filename)
{

}


GameObject::~GameObject()
{
}



void GameObject::render()
{
	model.draw(shader);
}

void GameObject::cleanUp()
{

}