#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class FullScreenQuad
{
public:
	
	unsigned int quadVAO;

	FullScreenQuad(Shader* screenShader, unsigned int texColorBuffer);

	void drawQuad();

private:

	Shader* screenShader;
	unsigned int textureColorBuffer;
};

