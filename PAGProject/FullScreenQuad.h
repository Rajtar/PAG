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

	bool& getRefDoToonShading();
	float& getRefToneExposure();
	float& getRefGammaCorection();

private:

	Shader* screenShader;
	unsigned int textureColorBuffer;

	bool doToonShading = false;
	float toneExposure = 1.0f;
	float gammaCorection = 0.5f;
};

