#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	void init(int width, int height);

	GLFWwindow* getWindow();

	Window();
	~Window();

private:
	GLFWwindow* window;
};

