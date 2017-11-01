#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Window.h"

class InputHandler
{
public:

	void processKeyboardInput(GLfloat deltaTime);
	void processMouseInput();

	glm::vec3 getCameraPos();
	glm::vec3 getCameraFront();
	glm::vec3 getCameraUp();

	InputHandler(Window* window);
	~InputHandler();

private:

	Window* window;

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	bool firstMouse = true;

	GLfloat lastX = 400; 
	GLfloat lastY = 300;
	GLfloat yaw;
	GLfloat pitch;

	GLfloat mouseSensitivity = 0.1;
};

