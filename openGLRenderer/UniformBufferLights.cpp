#include "UniformBufferLights.h"
#include <iostream>

UniformBufferLights::UniformBufferLights()
{
	this->setUBO();
}

UniformBufferLights::~UniformBufferLights()
{
}

void UniformBufferLights::setUBO()
{
	glGenBuffers(1, &this->UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, this->UBO);
}

void UniformBufferLights::updateLightPosition(glm::vec3 position)
{
	glm::vec4 pos = glm::vec4(position, 0.0);
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(pos));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}