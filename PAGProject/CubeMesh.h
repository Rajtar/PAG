#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "MeshBase.h"
#include <string>

class CubeMesh : public MeshBase
{
public:

	void loadContent(GLfloat size, std::string texturePath);
	virtual void renderMesh();

	CubeMesh();
	~CubeMesh();

private:
	unsigned int texture;
};

