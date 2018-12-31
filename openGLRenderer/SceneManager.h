#pragma once
class SceneManager
{
public:
	static SceneManager* getInstance();
private:
	static SceneManager* instance; // storing the instance
	SceneManager(); // private constructor to prevent instancing
};

