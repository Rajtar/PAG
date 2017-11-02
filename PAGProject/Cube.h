#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Cube
{
public:

	glm::vec3 vertices[36];
	glm::vec2 textureCoordinates[36];

	Cube(GLfloat size) :

		vertices{

		glm::vec3(-size, -size, -size),
		glm::vec3(size, -size, -size),
		glm::vec3(size,  size, -size),
		glm::vec3(size,  size, -size),
		glm::vec3(-size,  size, -size),
		glm::vec3(-size, -size, -size),

		glm::vec3(-size, -size,  size),
		glm::vec3(size, -size,  size),
		glm::vec3(size,  size,  size),
		glm::vec3(size,  size,  size),
		glm::vec3(-size,  size,  size),
		glm::vec3(-size, -size,  size),

		glm::vec3(-size,  size,  size),
		glm::vec3(-size,  size, -size),
		glm::vec3(-size, -size, -size),
		glm::vec3(-size, -size, -size),
		glm::vec3(-size, -size,  size),
		glm::vec3(-size,  size,  size),

		glm::vec3(size,  size,  size),
		glm::vec3(size,  size, -size),
		glm::vec3(size, -size, -size),
		glm::vec3(size, -size, -size),
		glm::vec3(size, -size,  size),
		glm::vec3(size,  size,  size),

		glm::vec3(-size, -size, -size),
		glm::vec3(size, -size, -size),
		glm::vec3(size, -size,  size),
		glm::vec3(size, -size,  size),
		glm::vec3(-size, -size,  size),
		glm::vec3(-size, -size, -size),

		glm::vec3(-size,  size, -size),
		glm::vec3(size,  size, -size),
		glm::vec3(size,  size,  size),
		glm::vec3(size,  size,  size),
		glm::vec3(-size,  size,  size),
		glm::vec3(-size,  size, -size)
	},

		textureCoordinates {

		glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),

			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),

			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),

			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),

			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f),

			glm::vec2(0.0f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 1.0f)
	} {}
};


//index drawing
//glm::vec3 vertices[] = {
//	//Bottom
//	glm::vec3(-0.5f, -0.5f,  0.5f),
//	glm::vec3(0.5f, -0.5f,  0.5f),
//	glm::vec3(0.5f, -0.5f, -0.5f),
//	glm::vec3(-0.5f, -0.5f, -0.5f),

//	//Top
//	glm::vec3(-0.5f, 0.5f,  0.5f),
//	glm::vec3(0.5f, 0.5f,  0.5f),
//	glm::vec3(0.5f, 0.5f, -0.5f),
//	glm::vec3(-0.5f, 0.5f, -0.5f)
//};

//GLuint indices[] = {
//	//Front
//	0, 1, 5,
//	0, 4, 5,

//	//Bottom
//	0, 1, 3,
//	1, 2, 3,  

//	//Top
//	4, 5, 7,
//	5, 6, 7,

//	//Back
//	2, 3, 6,
//	3, 6, 7,

//	//Left
//	0, 4, 7,
//	0, 3, 7,

//	//Right
//	1, 2, 6,
//	1, 5, 6,
//};

//GLuint EBO;
//glGenBuffers(1, &EBO);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);