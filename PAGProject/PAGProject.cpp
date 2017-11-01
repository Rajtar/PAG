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
#include "Camera.h"
#include "KeyboardHandler.h"

int main()
{
	Window* window = new Window();
	Mesh* mesh = new Mesh();

	try {

		window->init(620, 480);

		Program* program = new Program();

		Shader vertexShader;
		Shader fragmentShader;

		vertexShader.loadAndCompileShaderFromFile(GL_VERTEX_SHADER, "Shaders/basic.vert", (*program).programHandle);
		fragmentShader.loadAndCompileShaderFromFile(GL_FRAGMENT_SHADER, "Shaders/basic.frag", (*program).programHandle);

		program->linkProgram();
		program->activateProgram();

		KeyboardHandler* keyboardHandler = new KeyboardHandler(window);

		Camera camera(window, program, keyboardHandler);

		Camera* cameraPtr = &camera;

		

		Core core(window, cameraPtr, keyboardHandler);

		mesh->loadContent();
		core.addRenderable(mesh);
		core.update();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}