#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Postprocess
{
public:
	
	Postprocess();

	unsigned int framebuffer;
	unsigned int textureColorBuffer;
};

