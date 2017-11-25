#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "InitializationException.cpp"
#include "Program.h"
#include "Camera.h"
#include "InputHandler.h"
#include "GraphNode.h"
#include "Model.h"


int main()
{
	Window* window = new Window();

	try {

		window->init(800, 600);

		//Program* program = new Program();

		/*Shader vertexShader;
		Shader fragmentShader;

		vertexShader.loadAndCompileShaderFromFile(GL_VERTEX_SHADER, "Shaders/basic.vert", (*program).programHandle);
		fragmentShader.loadAndCompileShaderFromFile(GL_FRAGMENT_SHADER, "Shaders/basic.frag", (*program).programHandle);*/

		Shader ourShader("Shaders/final.vs", "Shaders/final.fs");

		Model ourModel("Models/nanosuit/nanosuit.obj");
		//Model ourModel("Models/human/human.blend");
		//Model ourModel("Models/chopper/chopper.obj");
		//Model ourModel("Models/van/van.max");
		//Model ourModel("Models/test/test.obj");

		//program->linkProgram();
		//program->activateProgram();

		InputHandler* inputHandler = new InputHandler(window);

		Camera camera(window, ourShader.id, inputHandler);

		Camera* cameraPtr = &camera;
		
		//GraphNode sceneRoot(NULL, NULL, program);


		//Core core(window, cameraPtr, inputHandler, &sceneRoot);
		Core core(window, cameraPtr, inputHandler, &ourModel, &ourShader);

		core.update();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}
