#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::load(const char* scene)
{
	string line;
	ifstream file(scene);
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
			std::string type;

			iss >> ignore >> id >> model_id >> shader_id >> px >> py >> pz >> sx >> sy >> sz >> type;
			this->entities[id] = new GameObject(this->shaders[shader_id], this->models[model_id], glm::vec3(px, py, pz), glm::vec3(sx, sy, sz));
		}
	}
}

void SceneManager::update(glm::mat4 view, glm::mat4 projection, float deltaTime)
{
	std::map<int, GameObject*>::iterator it = this->entities.begin();

	while (it != this->entities.end())
	{
		it->second->update(view, projection, deltaTime);
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