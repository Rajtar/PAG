#include "CubeMesh.h"
#include "Texture.h"
#include "Cube.h"

#include <iostream>

void CubeMesh::loadContent(GLfloat size, std::string texturePath)
{
	Cube cube(size);

	GLuint VBO = NULL;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube.vertices), cube.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	
	/*glm::vec3 colors[] = { glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),

		glm::vec3(0.0f, 0.0f,  1.0f),
		glm::vec3(0.0f, 0.0f,  1.0f),
		glm::vec3(0.0f, 1.0f,  1.0f),
		glm::vec3(0.0f, 1.0f,  1.0f)
	};

	GLuint VBO_colors = NULL;
	glGenBuffers(1, &VBO_colors);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);*/
	


	GLuint VBO_texture = NULL;
	glGenBuffers(1, &VBO_texture);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube.textureCoordinates), cube.textureCoordinates, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	Texture tex;
	tex.loadTexture(texturePath);
	texture = tex.getTextureHolder();
	glBindTexture(GL_TEXTURE_2D, texture);
}

void CubeMesh::renderMesh(Transform* transform)
{
	/*glm::mat4 trans = transform->transformation;
	trans = glm::rotate(trans, (GLfloat)glfwGetTime() * 50.0f, glm::vec3(1.0, 0.0, 0.0));
	transform->transformation = trans;*/

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6*6);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

CubeMesh::CubeMesh()
{
}


CubeMesh::~CubeMesh()
{
}