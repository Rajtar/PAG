#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "Transform.h"
#include <vector>
#include "Texture.h"
#include "Vertex.h"
#include "Shader.h"

class Mesh
{
public:

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int specialTexture = NULL;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void draw(Shader shader);
	void drawForPicking(Shader shader);

private:
	unsigned int VAO, VBO, EBO, pickingVAO, pickingVBO, pickingEBO;

	void setupMesh();
};

