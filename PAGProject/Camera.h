#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Window.h"
#include "Program.h"
#include "KeyboardHandler.h"


class Camera
{
public:

	void reloadCamera();

	Camera(Window* window, Program* program, KeyboardHandler* keyboardHandler);
	~Camera();

private:

	Window* window;
	Program* program;
	KeyboardHandler* keyboardHandler;
};

