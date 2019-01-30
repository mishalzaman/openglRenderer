#include "ModelManager.h"

ModelManager* ModelManager::instance = 0; // setting this to zero as instance wil be initialized on demand

ModelManager::ModelManager() {}

ModelManager* ModelManager::getInstance()
{
	if (instance == 0)
	{
		instance = new ModelManager();
	}

	return instance;
}

void ModelManager::add(int id, const char *filename)
{
	this->models[id] = new Model(filename);
}

Model ModelManager::get(int id)
{
	return *this->models.find(id)->second;
}

void ModelManager::cleanUp()
{
	for (auto it = this->models.cbegin(); it != this->models.cend();)
	{
		delete it->second;

		// erase() function returns the iterator of the next
		// to last deleted element.
		it = this->models.erase(it);
	}
}