#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Player.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

Player::Player(glm::vec3 position)
{
	this->position = position;

	this->yawQuat = glm::angleAxis(this->yaw, glm::vec3(0, 1, 0));
	glm::mat4 rotationMatrix = glm::toMat4(glm::normalize(this->yawQuat * this->pitchQuat * this->rollQuat));

	this->model = glm::translate(this->model, this->position) * rotationMatrix;
}


Player::~Player()
{
}

glm::mat4 Player::getModel(float deltaTime)
{
	return this->model;
}

glm::vec3 Player::getPosition()
{
	return this->position;
}

void Player::yawRight(float deltaTime)
{
	this->yaw -= this->rotationAngle;

	if (this->yaw < 0.0f)
	{
		this->yaw = 360.0f;
	}

	this->yawQuat = glm::angleAxis(this->yaw, glm::vec3(0, 1, 0));
	glm::mat4 rotationMatrix = glm::toMat4(glm::normalize(this->yawQuat * this->pitchQuat * this->rollQuat));

	this->model = glm::translate(glm::mat4(1.0f), this->position) * rotationMatrix;
}

void Player::yawLeft(float deltaTime)
{
	this->yaw += this->rotationAngle;

	if (this->yaw > 360.0f)
	{
		this->yaw = 0.0f;
	}

	this->yawQuat = glm::angleAxis(this->yaw, glm::vec3(0, 1, 0));
	glm::mat4 rotationMatrix = glm::toMat4(glm::normalize(this->yawQuat * this->pitchQuat * this->rollQuat));

	this->model = glm::translate(glm::mat4(1.0f), this->position) * rotationMatrix;
}

void Player::pitchUP(float deltaTime)
{
	this->pitch += this->rotationAngle;

	if (this->pitch > 360.0f)
	{
		this->pitch = 0.0f;
	}

	this->pitchQuat = glm::angleAxis(this->pitch, glm::vec3(0, 0, 1));
	glm::mat4 rotationMatrix = glm::toMat4(glm::normalize(this->yawQuat * this->pitchQuat * this->rollQuat));

	this->model = glm::translate(glm::mat4(1.0f), this->position) * rotationMatrix;
}

void Player::pitchDown(float deltaTime)
{
	this->pitch -= this->rotationAngle;

	if (this->pitch < 0.0f)
	{
		this->pitch = 360.0f;
	}

	this->pitchQuat = glm::angleAxis(this->pitch, glm::vec3(0, 0, 1));
	glm::mat4 rotationMatrix = glm::toMat4(glm::normalize(this->yawQuat * this->pitchQuat * this->rollQuat));

	this->model = glm::translate(glm::mat4(1.0f), this->position) * rotationMatrix;
}

void Player::accelerate(float deltaTime)
{
	// https://www.gamedev.net/forums/topic/56471-extracting-direction-vectors-from-quaternion/
	// https://www.allaboutcircuits.com/technical-articles/dont-get-lost-in-deep-space-understanding-quaternions/

	glm::mat4 rm = glm::toMat4(glm::normalize(this->yawQuat * this->pitchQuat * this->rollQuat));
	//cout << to_string(rm[0][0]) + ", " + to_string(rm[0][1]) + ", " + to_string(rm[0][2]) + ", " + to_string(rm[0][3]) << endl;
	//cout << to_string(rm[1][0]) + ", " + to_string(rm[1][1]) + ", " + to_string(rm[1][2]) + ", " + to_string(rm[1][3]) << endl;
	//cout << to_string(rm[2][0]) + ", " + to_string(rm[2][1]) + ", " + to_string(rm[2][2]) + ", " + to_string(rm[2][3]) << endl;
	//cout << to_string(rm[3][0]) + ", " + to_string(rm[3][1]) + ", " + to_string(rm[3][2]) + ", " + to_string(rm[3][3]) << endl;

	this->position -= glm::vec3(rm[0][0], rm[0][1], rm[0][2]) * 0.05f;
	this->position -= glm::vec3(rm[3][0], rm[3][1], rm[3][2]) * 0.05f;
	this->model = glm::translate(glm::mat4(1.0f), this->position) * rm;
}

void Player::reverse(float deltaTime)
{
	glm::mat4 rm = glm::toMat4(glm::normalize(this->yawQuat * this->pitchQuat * this->rollQuat));
	this->position += glm::vec3(rm[0][0], rm[0][1], rm[0][2]) * 0.05f;
	this->position += glm::vec3(rm[3][0], rm[3][1], rm[3][2]) * 0.05f;
	this->model = glm::translate(glm::mat4(1.0f), this->position) * rm;
}


