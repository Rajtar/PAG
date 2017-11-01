#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Window.h"

class KeyboardHandler
{
public:

	void processInput(GLfloat deltaTime);

	glm::vec3 getCameraPos();
	glm::vec3 getCameraFront();
	glm::vec3 getCameraUp();

	KeyboardHandler(Window* window);
	~KeyboardHandler();

private:

	Window* window;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};

