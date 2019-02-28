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
