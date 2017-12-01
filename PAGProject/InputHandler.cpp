#include "InputHandler.h"
#include <AntTweakBar/AntTweakBar.h>
#include <sstream>
#include <iostream>

void InputHandler::keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	TwEventKeyGLFW(key, action);
	TwEventCharGLFW(key, action);
}


void InputHandler::processKeyboardInput(GLfloat deltaTime, Window* window)
{
	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void InputHandler::mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (!TwEventMousePosGLFW(xpos, ypos))
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;
		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}
}

void InputHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if(!TwEventMouseButtonGLFW(button, action))
	{
		if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		{
			if (mouseCursorEnabled)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				mouseCursorEnabled = false;
			}
			else
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				mouseCursorEnabled = true;
			}
		}

		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			processPicking();
		}
	}
}

void InputHandler::processPicking()
{
	std::string message;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pickingShader->use();
	glEnableVertexAttribArray(0);

	sceneRoot.shader = pickingShader;

	sceneRoot.renderForPicking(Transform::origin());

	glDisableVertexAttribArray(0);

	glFlush();
	glFinish();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned char data[4];
	glReadPixels(1600 / 2, 900 / 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

	int pickedID =
		data[0] +
		data[1] * 256 +
		data[2] * 256 * 256;

	if (pickedID == 0x00ffffff) { // Full white, must be the background !
		message = "background";
	}
	else {
		std::ostringstream oss;
		oss << "mesh " << pickedID;
		message = oss.str();
	}
	std::cout << message << std::endl;
}

Shader* InputHandler::pickingShader;
GraphNode InputHandler::sceneRoot = NULL;

glm::vec3 InputHandler::cameraPos;
glm::vec3 InputHandler::cameraFront;
glm::vec3 InputHandler::cameraUp;

bool InputHandler::firstMouse = true;

GLfloat InputHandler::lastX = 400;
GLfloat InputHandler::lastY = 300;
GLfloat InputHandler::yaw;
GLfloat InputHandler::pitch;

GLfloat InputHandler::mouseSensitivity = 0.1;

bool InputHandler::mouseCursorEnabled = false;