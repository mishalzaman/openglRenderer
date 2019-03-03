#include "SceneManager.h"
#include "UniformBufferMatrices.h"
#include "UniformBufferLights.h"

using namespace std;

SceneManager::SceneManager(CameraFP &camera):
	camera(camera)
{
	this->uniformBuffersMatrices = new UniformBufferMatrices();
	this->uniformBuffersLights = new UniformBufferLights();
}

SceneManager::~SceneManager()
{
}

void SceneManager::load(const char* filename, glm::mat4 projection)
{
	this->loadSceneFile(filename);
	this->uniformBuffersMatrices->updateUBOMatricesProjection(projection);
}

void SceneManager::update(glm::mat4 view, float deltaTime)
{
	this->uniformBuffersMatrices->updateUBOMatricesView(view);

	std::map<int, GameObject*>::iterator itLight = this->getEntities("light").begin();
	while (itLight != this->getEntities("light").end())
	{
		GameObject &gameObject = *itLight->second;

		gameObject.update(deltaTime);
		this->uniformBuffersLights->updateLightPosition(gameObject.getPosition());
		itLight++;
	}

	std::map<int, GameObject*>::iterator itMaterial = this->getEntities("material").begin();
	while (itMaterial != this->getEntities("material").end())
	{
		itMaterial->second->update(deltaTime);
		itMaterial++;
	}
}

void SceneManager::draw()
{
	std::map<int, GameObject*>::iterator itLight = this->getEntities("light").begin();
	while (itLight != this->getEntities("light").end())
	{
		itLight->second->render();
		itLight++;
	}

	std::map<int, GameObject*>::iterator itMaterial = this->getEntities("material").begin();
	while (itMaterial != this->getEntities("material").end())
	{
		itMaterial->second->render();
		itMaterial++;
	}
}

std::map<int, GameObject*> &SceneManager::getEntities(std::string entity)
{
	if (entity == "light") { return this->lightEntities; };
	if (entity == "material") { return this->materialEntities; };
}

void SceneManager::loadSceneFile(const char* filename)
{
	string line;
	ifstream file(filename);
	while (getline(file, line))
	{
		if (line.substr(0, 2) == "SR")
		{
			std::istringstream iss(line);
			string ignore;
			int id;
			string vertex, fragment;

			iss >> ignore >> id >> vertex >> fragment;
			this->shaders[id] = new Shader(vertex.c_str(), fragment.c_str());
		}
		else if (line.substr(0, 2) == "ML")
		{
			std::istringstream iss(line);
			string ignore;
			int id;
			string file;

			iss >> ignore >> id >> file;
			this->models[id] = new Model(file.c_str());
		}
		else if (line.substr(0, 2) == "EN")
		{
			std::istringstream iss(line);
			string ignore;
			int id, model_id, shader_id;
			float px, py, pz, sx, sy, sz;
			string type;

			iss >> ignore >> id >> model_id >> shader_id >> px >> py >> pz >> sx >> sy >> sz >> type;

			if (type != "light")
			{
				this->materialEntities[id] = new GameObject(this->shaders[shader_id], this->models[model_id], this->camera, glm::vec3(px, py, pz), glm::vec3(sx, sy, sz));
				this->materialEntities[id]->setType(type);
			}
			else {
				this->lightEntities[id] = new GameObject(this->shaders[shader_id], this->models[model_id], this->camera, glm::vec3(px, py, pz), glm::vec3(sx, sy, sz));
				this->lightEntities[id]->setType(type);
			}
		}
	}
}