#include "Window.h"
#include "Shader.h"
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

	/*glViewport(0, 0, width, height);*/

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw InitializationException();
	}

	//TODO: move all the code below to another class
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLuint programHandle = glCreateProgram();
	
	if (programHandle == 0)
	{
		std::cerr<<"Error creating program object.\n";
	}

	//TODO: move to upper level
	Shader vertexShader;
	Shader fragmentShader;

	vertexShader.loadAndCompileShaderFromFile(GL_VERTEX_SHADER, "Shaders/basic.vert", programHandle);
	fragmentShader.loadAndCompileShaderFromFile(GL_FRAGMENT_SHADER, "Shaders/basic.frag", programHandle);

	glLinkProgram(programHandle);

	GLint linkingStatus;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &linkingStatus);

	if (linkingStatus == GL_FALSE)
	{
		std::cerr << "Failed to link shader program!\n";

		GLint logLength;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)
		{
			char* log = new char(logLength);

			GLsizei logRead;
			glGetProgramInfoLog(programHandle, logLength, &logRead, log);

			std::cerr << "Log:\n" << log << std::endl;

			delete log;
		}
	}

	glUseProgram(programHandle);

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
