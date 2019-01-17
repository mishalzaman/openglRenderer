/*
	Singleton Class: ModelManager
	------------------------------
	Concern: ModelManager is concerned with recieving an identifying name and the path to the model file.
	It then creates a Model object which contains vertices, indices etc.

	Why is this a singleton?
	------------------------
	I only require one instance of ModelManager, to basically manage the models that are to be used
	within a scene.
*/

#pragma once

#include "Model.h"

class ModelManager
{
public:
	static ModelManager* getInstance();
	void add(std::string name, const char *filename);
	Model get(std::string name);
	void cleanUp();
private:
	static ModelManager* instance; // storing the instance
	ModelManager(); // private constructor to prevent instancing

	std::map<std::string, Model*> models; // store a pointer to a Shader object
};

