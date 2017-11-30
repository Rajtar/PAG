#include "InputHandler.h"
#include <AntTweakBar/AntTweakBar.h>

void InputHandler::processKeyboardInput(GLfloat deltaTime)
{
	if (glfwGetKey(window->getWindow(), GLFW_KEY_5) == GLFW_PRESS)
		TwEventCharGLFW(GLFW_KEY_5, GLFW_PRESS);


	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void InputHandler::processMouseInput()
{
	int leftButton = glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_LEFT);
	if (leftButton == GLFW_PRESS)
	{
		TwEventMouseButtonGLFW(leftButton, GLFW_PRESS);
	}

	int rightButton = glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT);
	if (rightButton == GLFW_PRESS)
	{
		if(mouseCursorEnabled)
		{
			glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			mouseCursorEnabled = false;
		}
		else
		{
			glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseCursorEnabled = true;
		}
	}

	GLdouble xpos, ypos;
	glfwGetCursorPos(window->getWindow(), &xpos, &ypos);

	TwEventMousePosGLFW(xpos, ypos);

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

glm::vec3 InputHandler::getCameraPos()
{
	return cameraPos;
}

glm::vec3 InputHandler::getCameraFront()
{
	return cameraFront;
}

glm::vec3 InputHandler::getCameraUp()
{
	return cameraUp;
}


InputHandler::InputHandler(Window* window)
{
	this->window = window;

	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	cameraUp = glm::cross(cameraDirection, cameraRight);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
}


InputHandler::~InputHandler()
{
}