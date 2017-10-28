#include "Window.h"
#include "InitializationException.cpp"
#include <iostream>

void Window::init(int width, int height)
{
	if (!glfwInit()) {

		throw InitializationException();
	}

	window = glfwCreateWindow(width, height, "PAG-App", NULL, NULL);


	if (!window) {

		throw InitializationException();
	}

	glfwMakeContextCurrent(window);

	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw InitializationException();
	}
	
	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
}

GLFWwindow * Window::getWindow()
{
	return window;
}

Window::Window()
{
}


Window::~Window()
{
}
