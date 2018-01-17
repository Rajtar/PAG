#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "Shader.h"
#include "Camera.h"

class Skybox
{
public:
	Skybox(std::vector<std::string> faces, Shader* shader);

	void render();

	unsigned int textureId;

private:

	std::vector<std::string> faces;
	unsigned int skyboxVAO;

	Shader* shader;

	void loadCubemap();
	void prepareVAO();
};

