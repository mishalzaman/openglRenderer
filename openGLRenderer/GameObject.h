#include "Shader.h"
#include "Model.h"

class GameObject
{
public:
	Shader shader;
	Model model;
	GameObject(const char* vertexPath, const char* fragmentPath, const char *filename);
	~GameObject();
	void render();
	void cleanUp();
};

