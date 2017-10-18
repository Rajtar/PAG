#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Renderable.h"

class Mesh : public Renderable
{
public:

	void loadContent();
	virtual void render();

	Mesh();
	~Mesh();

private:
	unsigned int texture;
};

