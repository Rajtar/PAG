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
#include "Program.h"

int main()
{
	Window* window = new Window();
	Core core(window);
	Mesh* mesh = new Mesh();

	try {

		window->init(620, 480);

		Program program;

		Shader vertexShader;
		Shader fragmentShader;

		vertexShader.loadAndCompileShaderFromFile(GL_VERTEX_SHADER, "Shaders/basic.vert", program.programHandle);
		fragmentShader.loadAndCompileShaderFromFile(GL_FRAGMENT_SHADER, "Shaders/basic.frag", program.programHandle);

		program.linkProgram();
		program.activateProgram();


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
		GLuint wvpLoc = glGetUniformLocation(program.programHandle, "wvp");
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