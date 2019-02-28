#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class UniformBuffer
{
public:
	UniformBuffer(unsigned int shaderID);
	~UniformBuffer();

	/*	uniform Matrices
			mat4 projection;
			mat4 view;
	*/
	void updateUBOMatricesProjection(glm::mat4 projection);
	void updateUBOMatricesView(glm::mat4 view);
private:
	unsigned int shaderID;

	unsigned int UBOMatrices;
	void setUBOMatrices();
	void setMatricesUniformBlock();
};

