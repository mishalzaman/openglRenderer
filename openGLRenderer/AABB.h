#pragma once

#include "Mesh.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <algorithm> 

// Axis-Aligned Bounding Box
// https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

class AABB
{
public:
	AABB();
	~AABB();
	void setBounds(std::vector<Vertex> vertices);
	bool isInside(AABB other);
	void render(glm::mat4 projection, glm::mat4 view, glm::vec3 position);
private:
	Shader shader;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	int shaderProgram;
	float xMin = 0.0;
	float xMax = 0.0;
	float yMin = 0.0;
	float yMax = 0.0;
	float zMin = 0.0;
	float zMax = 0.0;
	void setBbVertices();
};

