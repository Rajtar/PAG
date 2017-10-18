#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"

class Core
{
public:
	void update();
	void render();

	Core(Window* window);
	~Core();

private:
	Window* window;
};

