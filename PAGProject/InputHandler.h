#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Window.h"
#include "Shader.h"
#include "GraphNode.h"

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

	static bool firstMouse;

	static GLfloat lastX;
	static GLfloat lastY;
	static GLfloat yaw;
	static GLfloat pitch;

	static GLfloat mouseSensitivity;

	static bool mouseCursorEnabled;

	static bool pickingMode;
};

