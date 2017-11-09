#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "MeshBase.h"
#include "Transform.h"

class CubeMesh : public MeshBase
{
public:

	void loadContent(GLfloat size, std::string texturePath);
	virtual void renderMesh(Transform* transform);

	CubeMesh();
	~CubeMesh();

private:
	unsigned int texture;
};

