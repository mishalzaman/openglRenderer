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
	/*
		uniform Lights
			vec3 lightColour;
			vec3 lightPosition;
			vec3 cameraPosition;
			vec3 lightAmbient;
			vec3 lightDiffuse;
			vec3 lightSpecular;
	*/
	void updateUBOLightColour(glm::vec4 colour);
	void updateUBOLightPosition(glm::vec4 position);
	void updateUBOLightCameraPosition(glm::vec4 cameraPosition);
	void updateUBOLightAmbient(glm::vec4 ambient);
	void updateUBOLightDiffuse(glm::vec4 diffuse);
	void updateUBOLightSpecular(glm::vec4 specular);
private:
	unsigned int shaderID;

	unsigned int UBOMatrices;
	void setUBOMatrices();
	void setMatricesUniformBlock();

	unsigned int UBOLights;
	void setUBOLights();
	void setLightsUniformBuffer();
};

