#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <AntTweakBar/AntTweakBar.h>

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
#include "ModelLoader.h"
#include "Cube.h"
#include "SpinModificator.h"


int main()
{
	Window* window = new Window();
	
	try {

		int windowWidth, windowHeight;

		windowWidth = 1600;
		windowHeight = 900;

		window->init(windowWidth, windowHeight);

		TwInit(TW_OPENGL, NULL);
		TwWindowSize(windowWidth, windowHeight);


		TwBar *myBar;
		myBar = TwNewBar("Scene");
		TwAddVarRW(myBar, "Test", TW_TYPE_INT16, &windowHeight, "");

		//Program* program = new Program();

		/*Shader vertexShader;
		Shader fragmentShader;

		vertexShader.loadAndCompileShaderFromFile(GL_VERTEX_SHADER, "Shaders/basic.vert", (*program).programHandle);
		fragmentShader.loadAndCompileShaderFromFile(GL_FRAGMENT_SHADER, "Shaders/basic.frag", (*program).programHandle);*/

		Shader ourShader("Shaders/final.vs", "Shaders/final.fs");


		//Model ourModel("Models/nanosuit/nanosuit.obj");
		//Model ourModel("Models/human/human.blend");
		//Model ourModel("Models/chopper/chopper.obj");
		//Model ourModel("Models/van/van.max");
		//Model ourModel("Models/test/test.obj");

		//program->linkProgram();s
		//program->activateProgram();
		GraphNode sceneRoot(&ourShader);

		ModelLoader loader;

		loader.loadModel("Models/nanosuit/nanosuit.obj", &sceneRoot, &ourShader);
		//loader.loadModel("Models/human/human.blend", &sceneRoot, &ourShader);
		//loader.loadModel("Models/ironman/Iron_Man.dae", &sceneRoot, &ourShader);
		//loader.loadModel("Models/Spider-Man_Modern/Spider-Man_Modern.dae", &sceneRoot, &ourShader);
		//loader.loadModel("Models/shapes/shapes.FBX", &sceneRoot, &ourShader);

		/*Cube cube(0.5f);
		std::vector<Texture> stub;
		Mesh testMesh(cube.vertices, cube.indices, stub);
		sceneRoot.meshes.push_back(testMesh);*/

		SpinModificator spin(glm::vec3(0.0f, 1.0f, 0.0f), 0.005f);

		Transform t;
		//t.modificator = &spin;
		t.transformation = glm::translate(t.transformation, glm::vec3(0.0f, 0.0f, 10.0f));
		//t.transformation = glm::scale(t.transformation, glm::vec3(0.01f, 0.01f, 0.01f));

		//sceneRoot.children[0]->children[0]->children[0]->local = t;

		InputHandler* inputHandler = new InputHandler(window);

		Camera camera(window, ourShader.id, inputHandler);

		Camera* cameraPtr = &camera;
		
		//GraphNode sceneRoot(NULL, NULL, program);


		Core core(window, cameraPtr, inputHandler, &sceneRoot, &ourShader);
		//Core core(window, cameraPtr, inputHandler, &ourModel, &ourShader);

		core.update();
		TwTerminate();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}
