#include "FullScreenQuad.h"
#include "ModelLoader.h"

FullScreenQuad::FullScreenQuad(Shader* screenShader, unsigned int textureColorBuffer)
{
	this->screenShader = screenShader;
	this->textureColorBuffer = textureColorBuffer;

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	unsigned int quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void FullScreenQuad::drawQuad()
{
	screenShader->use();

	screenShader->setBool("doToonShading", doToonShading);
	screenShader->setBool("doPixelationShading", doPixelationShading);
	screenShader->setFloat("toneExposure", toneExposure);
	screenShader->setFloat("gamma", gammaCorection);

	glBindVertexArray(quadVAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

bool& FullScreenQuad::getRefDoToonShading()
{
	return doToonShading;
}

bool& FullScreenQuad::getRefDoPixelationShading()
{
	return  doPixelationShading;
}

float& FullScreenQuad::getRefToneExposure()
{
	return toneExposure;
}

float& FullScreenQuad::getRefGammaCorection()
{
	return gammaCorection;
}
