#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

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

		/****************************/
		/* Set world matrix to identity matrix */
		glm::mat4 world = glm::mat4(1.0f);

		/* Set view matrix */
		glm::mat4 view = glm::lookAt(glm::vec3(1.5f, 0.0f, 1.5f),  // camera position in world space
			glm::vec3(0.0f, 0.0f, 0.0f),  // at this point camera is looking
			glm::vec3(0.0f, 1.0f, 0.0f)); // head is up

										  /* Set projection matrix */
		int w;
		int h;
		glfwGetWindowSize(window->getWindow(), &w, &h);

		glm::mat4 projection = glm::perspective(45.0f, (float)w / (float)h, 0.001f, 50.0f);

		/* Set MVP matrix */
		glm::mat4 WVP = projection * view * world;

		/* Get uniform location and send MVP matrix there */
		GLuint wvpLoc = glGetUniformLocation(programHandle, "wvp");
		glUniformMatrix4fv(wvpLoc, 1, GL_FALSE, &WVP[0][0]);
		/****************************/

		mesh->loadContent();
		core.addRenderable(mesh);
		core.update();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}