#include "Camera.h"

#include <iostream>


void Camera::reloadCamera()
{
	glm::mat4 world = glm::mat4(1.0f);

	glm::vec3 cameraPos = InputHandler::cameraPos;
	glm::vec3 cameraFront = InputHandler::cameraFront;
	glm::vec3 cameraUp = InputHandler::cameraUp;

	glm::mat4 view;
	view = view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	
	int w, h;
	glfwGetWindowSize(window->getWindow(), &w, &h);

	glm::mat4 projection = glm::perspective(45.0f, (float)w / (float)h, 0.001f, 50.0f);

	glm::mat4 WVP = projection * view * world;

	//GLuint wvpLoc = glGetUniformLocation(program->programHandle, "wvp");
	GLuint wvpLoc = glGetUniformLocation(programId, "wvp");
	glUniformMatrix4fv(wvpLoc, 1, GL_FALSE, &WVP[0][0]);

	GLuint modelLoc = glGetUniformLocation(programId, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &world[0][0]);
}

//Program * Camera::getProgram()
//{
//	return program;
//}

Camera::Camera(Window* window, /*Program* program*/ GLuint programId)
{
	this->window = window;
	//this->program = program;
	this->programId = programId;
}


Camera::~Camera()
{
}
