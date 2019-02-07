#include "AABB.h"
#include <iostream>

using namespace std;

AABB::AABB()
{
}


AABB::~AABB()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	delete(this->shader);
}

void AABB::setBounds(std::vector<Vertex> vertices)
{
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		this->xMin = std::min(this->xMin, vertices[i].Position.x);
		this->xMax = std::max(this->xMax, vertices[i].Position.x);
		this->yMin = std::min(this->yMin, vertices[i].Position.y);
		this->yMax = std::max(this->yMax, vertices[i].Position.y);
		this->zMin = std::min(this->zMin, vertices[i].Position.z);
		this->zMax = std::max(this->zMax, vertices[i].Position.z);
	}

	this->setBbVertices();
}

bool AABB::isInside(AABB other)
{
	//cout << "this->xMax < other.xMin" + to_string(this->xMax) + " " + to_string(other.xMin) << endl;
	//cout << "this->yMax < other.yMin" + to_string(this->yMax) + " " + to_string(other.yMin) << endl;
	//cout << "this->xMin > other.xMax" + to_string(this->xMin) + " " + to_string(other.xMax) << endl;
	//cout << "this->yMin > other.yMax" + to_string(this->yMin) + " " + to_string(other.yMax) << endl;
	//cout << "-------" << endl;

	return (this->xMax < other.xMin ||
		this->yMax < other.yMin ||
		this->xMin > other.xMax ||
		this->yMin > other.yMax);
}

void AABB::setBbVertices()
{
	this->vertices = {
		this->xMin, this->yMin, this->zMin,
		this->xMax, this->yMin, this->zMin,
		this->xMax, this->yMax, this->zMin,
		this->xMin, this->yMax, this->zMin,
		this->xMin, this->yMin, this->zMax,
		this->xMax, this->yMin, this->zMax,
		this->xMax, this->yMax, this->zMax,
		this->xMin, this->yMax, this->zMax
	};

	this->indices = {  // note that we start from 0!
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void AABB::updateBounds(glm::mat4 modelMatrix)
{

}

void AABB::render(glm::mat4 projection, glm::mat4 view, glm::vec3 position, glm::vec3 scale)
{
	this->shader->use();
	this->shader->setMat4("projection", projection);
	this->shader->setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	this->shader->setMat4("model", model);
	glBindVertexArray(this->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}
