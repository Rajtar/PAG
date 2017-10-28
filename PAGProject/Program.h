#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Program
{
public:

	void linkProgram();
	void activateProgram();

	Program();
	~Program();

	GLuint programHandle;
};

