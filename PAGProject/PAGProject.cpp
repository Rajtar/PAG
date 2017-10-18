#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "InitializationException.cpp"
#include "Renderable.h"

int main()
{
	Window* window = new Window();
	Core core(window);
	Mesh* mesh = new Mesh();

	try {

		window->init(620, 480);

		GLuint programHandle = glCreateProgram();

		if (programHandle == 0)
		{
			std::cerr << "Error creating program object.\n";
		}

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

		mesh->loadContent();
		core.addRenderable(mesh);
		core.update();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}