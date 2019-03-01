#include "SceneManager.h"

using namespace std;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::load(const char* filename, glm::mat4 projection)
{
	this->loadSceneFile(filename);

	// set the projection matrix
	for (int i = 0; i < this->uniformBuffers.size(); i++) {
		this->uniformBuffers[i]->updateUBOMatricesProjection(projection);
	}
}

void SceneManager::update(glm::mat4 view, glm::vec3 cameraPosition, float deltaTime)
{
	for (int i = 0; i < this->uniformBuffers.size(); i++) {
		this->uniformBuffers[i]->updateUBOMatricesView(view);
	}

	std::map<int, GameObject*>::iterator it = this->entities.begin();
	while (it != this->entities.end())
	{
		it->second->update(deltaTime);
		it++;
	}
}

void SceneManager::draw()
{
	std::map<int, GameObject*>::iterator it = this->entities.begin();

	while (it != this->entities.end())
	{
		it->second->render();
		it++;
	}
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
			this->uniformBuffers.push_back(new UniformBuffer(this->shaders[id]->ID));
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
			std::string type;

			iss >> ignore >> id >> model_id >> shader_id >> px >> py >> pz >> sx >> sy >> sz >> type;
			this->entities[id] = new GameObject(this->shaders[shader_id], this->models[model_id], glm::vec3(px, py, pz), glm::vec3(sx, sy, sz));
			this->entities[id]->setType(type);
		}
	}
}