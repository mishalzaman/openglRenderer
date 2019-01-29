#include "SceneManager.h"

SceneManager::SceneManager() {
}

SceneManager::~SceneManager()
{
}

void SceneManager::loadScene(const char* scene)
{
	string line;
	ifstream file(scene);
	while (getline(file, line))
	{
		if (line[0] == 'S')
		{
			std::istringstream iss(line);
			char ignore;
			int id;
			string vertex, fragment;

			iss >> ignore >> id >> vertex >> fragment;
			this->shaders->create(id, vertex.c_str(), fragment.c_str());
		}
	}
}