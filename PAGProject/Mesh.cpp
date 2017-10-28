#include "Mesh.h"
#include "Texture.h"


void Mesh::loadContent()
{
	glm::vec3 vertices[] = { glm::vec3(-0.5f, -0.5f,  0.5f), //basis
		glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(-0.5f, -0.5f, -0.5f), //left side
		glm::vec3(-0.5f, -0.5f,  0.5f),
		glm::vec3(0.0f,  0.5f,  0.0f),
		glm::vec3(0.5f, -0.5f,  0.5f), //right side
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f,  0.5f,  0.0f),
		glm::vec3(-0.5f, -0.5f,  0.5f), //front side
		glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(0.0f,  0.5f,  0.0f),
		glm::vec3(0.5f, -0.5f, -0.5f), //back side
		glm::vec3(-0.5f, -0.5f, -0.5f),
		glm::vec3(0.0f,  0.5f,  0.0f) };

	GLuint VBO = NULL;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	
	glm::vec3 colors[] = { glm::vec3(1.0f, 0.0f,  0.0f), //basis
		glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(1.0f, 0.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f), //left side
		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 0.0f,  1.0f), //right side
		glm::vec3(0.0f, 0.0f,  1.0f),
		glm::vec3(0.0f, 0.0f,  1.0f),
		glm::vec3(1.0f, 1.0f,  0.0f), //front side
		glm::vec3(1.0f, 1.0f,  0.0f),
		glm::vec3(1.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  1.0f), //back side
		glm::vec3(0.0f, 1.0f,  1.0f),
		glm::vec3(0.0f, 1.0f,  1.0f)
	};

	GLuint VBO_colors = NULL;
	glGenBuffers(1, &VBO_colors);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	/*
	glm::vec2 textureCoords[] = { glm::vec2(0.0f,  0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.5f, 1.0f)
	};

	/*GLuint VBO_texture = NULL;
	glGenBuffers(1, &VBO_texture);
	glBindBuffer(GL_TEXTURE_BUFFER, VBO_texture);
	glBufferData(GL_TEXTURE_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	Texture tex;
	tex.loadTexture("Textures/grass.jpg");
	texture = tex.getTextureHolder();
	glBindTexture(GL_TEXTURE_2D, texture);*/
}

void Mesh::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3*6);
}

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}
