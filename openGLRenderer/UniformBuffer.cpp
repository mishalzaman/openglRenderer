#include "UniformBuffer.h"

using namespace std;

UniformBuffer::UniformBuffer(unsigned int shaderID)
{
	this->shaderID = shaderID;
	this->setMatricesUniformBlock();
	this->setUBOMatrices();
}

UniformBuffer::~UniformBuffer()
{
}

void UniformBuffer::setUBOMatrices()
{
	glGenBuffers(1, &this->UBOMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, this->UBOMatrices, 0, 2 * sizeof(glm::mat4));
}

void UniformBuffer::setMatricesUniformBlock()
{
	// get the uniform block indices
	unsigned int uniformBlockIndex = glGetUniformBlockIndex(this->shaderID, "Matrices");
	// link the shader's uniform block to the uniform binding point
	glUniformBlockBinding(this->shaderID, uniformBlockIndex, 0);
}

void UniformBuffer::updateUBOMatricesProjection(glm::mat4 projection)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::updateUBOMatricesView(glm::mat4 view)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::setUBOLights()
{
	glGenBuffers(1, &this->UBOLights);
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOLights);
	glBufferData(GL_UNIFORM_BUFFER, 6 * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 1, this->UBOLights, 0, 6 * sizeof(glm::vec4));
}

void UniformBuffer::setLightsUniformBuffer()
{
	// get the uniform block indices
	unsigned int uniformBlockIndex = glGetUniformBlockIndex(this->shaderID, "Light");
	// link the shader's uniform block to the uniform binding point
	glUniformBlockBinding(this->shaderID, uniformBlockIndex, 0);
}

void UniformBuffer::updateUBOLightColour(glm::vec4 colour)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOLights);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(colour));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::updateUBOLightPosition(glm::vec4 position)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOLights);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(position));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::updateUBOLightCameraPosition(glm::vec4 cameraPosition)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOLights);
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(cameraPosition));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::updateUBOLightAmbient(glm::vec4 ambient)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOLights);
	glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(ambient));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::updateUBOLightDiffuse(glm::vec4 diffuse)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOLights);
	glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(diffuse));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::updateUBOLightSpecular(glm::vec4 specular)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOLights);
	glBufferSubData(GL_UNIFORM_BUFFER, 5 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(specular));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
