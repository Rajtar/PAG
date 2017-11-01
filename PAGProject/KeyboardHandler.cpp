#include "KeyboardHandler.h"


void KeyboardHandler::processInput(GLfloat deltaTime)
{

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

glm::vec3 KeyboardHandler::getCameraPos()
{
	return cameraPos;
}

glm::vec3 KeyboardHandler::getCameraFront()
{
	return cameraFront;
}

glm::vec3 KeyboardHandler::getCameraUp()
{
	return cameraUp;
}

KeyboardHandler::KeyboardHandler(Window* window)
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


KeyboardHandler::~KeyboardHandler()
{
}
