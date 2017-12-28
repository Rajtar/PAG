#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Window.h"
#include "InputHandler.h"


class Camera
{
public:

	void reloadCamera();
	Camera(Window* window, GLuint programId);
	~Camera();

private:

	Window* window;
	GLuint programId;
};

