#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Window.h"
#include "Program.h"
#include "InputHandler.h"


class Camera
{
public:

	void reloadCamera();
	Program* getProgram();

	Camera(Window* window, Program* program, InputHandler* inputHandler);
	~Camera();

private:

	Window* window;
	Program* program;
	InputHandler* inputHandler;
};

