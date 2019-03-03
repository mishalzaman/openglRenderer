#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class UniformBufferLights
{
public:
	UniformBufferLights();
	~UniformBufferLights();
	void updateLightPosition(glm::vec3 position);
private:
	unsigned int UBO;
	void setUBO();
};

