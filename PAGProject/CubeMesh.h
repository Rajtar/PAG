#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "MeshBase.h"
#include "Transform.h"
#include <vector>

class CubeMesh : public MeshBase
{
public:

	void loadContent(GLfloat size);
	void addTexture(unsigned int texture);
	virtual void renderMesh(Transform* transform, int textureIndex);

	CubeMesh();
	~CubeMesh();

private:
	std::vector<unsigned int> textures;
};

