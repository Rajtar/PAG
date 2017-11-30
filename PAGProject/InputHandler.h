#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Window.h"

class InputHandler
{
public:

	void static keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void static mousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	void static mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void static processKeyboardInput(GLfloat deltaTime, Window* window);


	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;
	static glm::vec3 cameraUp;

	static bool firstMouse;// = true;

	static GLfloat lastX;// = 400;
	static GLfloat lastY;// = 300;
	static GLfloat yaw;
	static GLfloat pitch;

	static GLfloat mouseSensitivity;// = 0.1;

	static bool mouseCursorEnabled;// = false;
};

