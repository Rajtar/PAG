#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

#include "Core.h"
#include "Window.h"
#include "CubeMesh.h"
#include "Shader.h"
#include "InitializationException.cpp"
#include "Program.h"
#include "Camera.h"
#include "InputHandler.h"
#include "GraphNode.h"

int main()
{
	Window* window = new Window();

	try {

		window->init(800, 600);

		Program* program = new Program();

		Shader vertexShader;
		Shader fragmentShader;

		vertexShader.loadAndCompileShaderFromFile(GL_VERTEX_SHADER, "Shaders/basic.vert", (*program).programHandle);
		fragmentShader.loadAndCompileShaderFromFile(GL_FRAGMENT_SHADER, "Shaders/basic.frag", (*program).programHandle);

		program->linkProgram();
		program->activateProgram();

		InputHandler* inputHandler = new InputHandler(window);

		Camera camera(window, program, inputHandler);

		Camera* cameraPtr = &camera;
		
		GraphNode sceneRoot(NULL);
		
		CubeMesh* cubeMesh = new CubeMesh();
		cubeMesh->loadContent();

		GraphNode cube(cubeMesh);

		sceneRoot.appendChild(&cube);

		GraphNode* rootPtr = &sceneRoot;

		Core core(window, cameraPtr, inputHandler, rootPtr);

		core.update();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}