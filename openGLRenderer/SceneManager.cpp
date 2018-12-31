#include "SceneManager.h"

SceneManager* SceneManager::instance = 0; // setting this to zero as instance wil be initialized on demand

SceneManager::SceneManager() {}

SceneManager* SceneManager::getInstance()
{
	if (instance == 0)
	{
		instance = new SceneManager();
	}

	return instance;
}