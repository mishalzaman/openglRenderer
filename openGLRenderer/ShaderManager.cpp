#include "ShaderManager.h"
#include <iostream>

using namespace std;

ShaderManager* ShaderManager::instance = 0; // setting this to zero as instance wil be initialized on demand

ShaderManager::ShaderManager(){}

ShaderManager* ShaderManager::getInstance()
{
	if (instance == 0)
	{
		instance = new ShaderManager();
	}

	return instance;
}

void ShaderManager::add(std::string name, const char* vertexPath, const char* fragmentPath)
{
	this->shaders[name] = new Shader(vertexPath, fragmentPath);
}

Shader ShaderManager::get(std::string name)
{
	return *this->shaders.find(name)->second;
}

void ShaderManager::cleanUp()
{
	for (auto it = this->shaders.cbegin(); it != this->shaders.cend();)
	{
		glDeleteProgram(it->second->ID);

		// erase() function returns the iterator of the next
		// to last deleted element.
		it = this->shaders.erase(it);
	}
}