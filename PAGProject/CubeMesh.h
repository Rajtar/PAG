#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "MeshBase.h"

class CubeMesh : public MeshBase
{
public:

	void loadContent();
	virtual void renderMesh();

	CubeMesh();
	~CubeMesh();

private:
	unsigned int texture;
};

