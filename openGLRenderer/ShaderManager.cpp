#include "ShaderManager.h"

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
	std::map<std::string, Shader*>::iterator it = this->shaders.begin();

	while (it != this->shaders.end())
	{
		// might want to delete the shader object too?
		this->shaders.erase(it);
	}
}