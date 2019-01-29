/*
	Singleton Class: ShaderManager
	------------------------------
	Concern: ShaderManager is concerned with recieving an identifying name, vertex and fragment shader.
	Then it creates a shader program and stores it in a map.
	It can then return a stored shader based on its _name_.

	Why is this a singleton?
	------------------------
	I only require one instance of ShaderManager, to basically manage the shaders that are to be used
	within a scene.
*/

#pragma once

#include <map>
#include "Shader.h"

class ShaderManager
{
public:
	static ShaderManager* getInstance();
	void add(std::string name, const char* vertexPath, const char* fragmentPath);
	void create(int id, const char* vertexPath, const char* fragmentPath);
	Shader get(std::string name);
	void cleanUp();
private:
	static ShaderManager* instance; // storing the instance
	ShaderManager(); // private constructor to prevent instancing

	std::map<std::string, Shader*> shaders; // store a pointer to a Shader object
	std::map<int, Shader*> shader; // new
};

