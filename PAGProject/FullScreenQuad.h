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
	bool& getRefDoPixelationShading();
	float& getRefToneExposure();
	float& getRefGammaCorection();

private:

	Shader* screenShader;
	unsigned int textureColorBuffer;

	bool doToonShading = false;
	bool doPixelationShading = false;
	float toneExposure = 1.6f;
	float gammaCorection = 1.2f;
};

