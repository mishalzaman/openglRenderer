#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "stb_image.h"

class Shader;

class SkyBox
{
public:
	SkyBox();
	~SkyBox();
	void load();
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
private:
	void loadCubeMap();
	void loadCube();
	unsigned int textureID;
	unsigned int VAO;
	unsigned int VBO;
	Shader* shader;
	std::vector<std::string> faces = {
		"assets/skybox/right.jpg",
		"assets/skybox/left.jpg",
		"assets/skybox/top.jpg",
		"assets/skybox/bottom.jpg",
		"assets/skybox/front.jpg",
		"assets/skybox/back.jpg"
	};
};

