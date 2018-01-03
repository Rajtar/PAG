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
#include "Camera.h"
#include "InputHandler.h"
#include "GraphNode.h"
#include "Model.h"
#include "ModelLoader.h"
#include "Cube.h"
#include "SpinModificator.h"
#include <ctime>
#include <map>
#include "TransformInfo.h"


int main()
{
	Window* window = new Window();
	
	try {

		int windowWidth, windowHeight;

		windowWidth = 1280;
		windowHeight = 720;

		/*windowWidth = 800;
		windowHeight = 600;*/

		window->init(windowWidth, windowHeight);

		InputHandler::cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(InputHandler::cameraPos - cameraTarget);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

		InputHandler::cameraUp = glm::cross(cameraDirection, cameraRight);
		InputHandler::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

		glfwSetCursorPosCallback(window->getWindow(), InputHandler::mousePositionCallback);
		glfwSetKeyCallback(window->getWindow(), InputHandler::keyboardKeyCallback);
		glfwSetMouseButtonCallback(window->getWindow(), InputHandler::mouseButtonCallback);


		TwInit(TW_OPENGL, NULL);
		TwWindowSize(windowWidth, windowHeight);

		TransformInfo* transformInfo = new TransformInfo;

		TwBar *transformBar = TwNewBar("Transform");

		TwAddSeparator(transformBar, NULL, " group='Translation' ");
		TwAddVarRW(transformBar, "Translate X", TW_TYPE_FLOAT, &transformInfo->translateX, "group='Translation' step=0.1");
		TwAddVarRW(transformBar, "Translate Y", TW_TYPE_FLOAT, &transformInfo->translateY, "group='Translation' step=0.1");
		TwAddVarRW(transformBar, "Translate Z", TW_TYPE_FLOAT, &transformInfo->translateZ, "group='Translation' step=0.1");

		TwAddSeparator(transformBar, NULL, " group='Rotation' ");
		TwAddVarRW(transformBar, "Rotate X", TW_TYPE_FLOAT, &transformInfo->rotateX, "group='Rotation'");
		TwAddVarRW(transformBar, "Rotate Y", TW_TYPE_FLOAT, &transformInfo->rotateY, "group='Rotation'");
		TwAddVarRW(transformBar, "Rotate Z", TW_TYPE_FLOAT, &transformInfo->rotateZ, "group='Rotation'");
		TwAddVarRW(transformBar, "Rotate Angle", TW_TYPE_FLOAT, &transformInfo->rotateAngle, "group='Rotation' step=0.1");

		TwAddSeparator(transformBar, NULL, " group='Scale' ");
		TwAddVarRW(transformBar, "Scale X", TW_TYPE_FLOAT, &transformInfo->scaleX, "group='Scale' step=0.1");
		TwAddVarRW(transformBar, "Scale Y", TW_TYPE_FLOAT, &transformInfo->scaleY, "group='Scale' step=0.1");
		TwAddVarRW(transformBar, "Scale Z", TW_TYPE_FLOAT, &transformInfo->scaleZ, "group='Scale' step=0.1");


		Shader drawingShader("Shaders/final.vs", "Shaders/final.fs");
		Shader pickingShader("Shaders/picking.vs", "Shaders/picking.fs");


		GraphNode sceneRoot(&drawingShader, &pickingShader);

		GraphNode model1(&drawingShader, &pickingShader);
		GraphNode model2(&drawingShader, &pickingShader);

		GraphNode redCube(&drawingShader, &pickingShader);
		GraphNode greenCube(&drawingShader, &pickingShader);
		GraphNode blueCube(&drawingShader, &pickingShader);


		ModelLoader loader;

		loader.loadModelOmmitingRoot("Models/CubeRed/CubeRed.obj", &redCube, &drawingShader, &pickingShader);
		loader.loadModelOmmitingRoot("Models/CubeGreen/CubeGreen.obj", &greenCube, &drawingShader, &pickingShader);
		loader.loadModelOmmitingRoot("Models/CubeBlue/CubeBlue.obj", &blueCube, &drawingShader, &pickingShader);

		loader.loadModel("Models/nanosuit/nanosuit.obj", &model1, &drawingShader, &pickingShader);
		
		loader.loadModel("Models/Spider-Man_Modern/Spider-Man_Modern.dae", &model2, &drawingShader, &pickingShader);


		//model2.local.transformation = glm::translate(model2.local.transformation, glm::vec3(0, 3.0, 0));
		//model2.local.transformation = glm::scale(model2.local.transformation, glm::vec3(0.01f, 0.01f, 0.01f));

		redCube.local.transformation = glm::translate(redCube.local.transformation, glm::vec3(0, 3.0, 0));
		redCube.local.transformation = glm::scale(redCube.local.transformation, glm::vec3(0.01f, 0.01f, 0.01f));
		
		SpinModificator spin(glm::vec3(1.0f, 0.0f, 0.0f), 0.01);

		//redCube.local.modificator = &spin;

		greenCube.local.transformation = glm::translate(greenCube.local.transformation, glm::vec3(0.0, 1.0, 40.0));
		blueCube.local.transformation = glm::translate(blueCube.local.transformation, glm::vec3(50.0, 2.0, 0.0));


		//redCube.appendChild(&greenCube);
		//greenCube.appendChild(&blueCube);
		//sceneRoot.appendChild(&redCube);

		sceneRoot.appendChild(&redCube);
		sceneRoot.appendChild(&greenCube);
		sceneRoot.appendChild(&blueCube);

		sceneRoot.children[0] = &blueCube;
		sceneRoot.children[1] = &greenCube;
		sceneRoot.children[2] = &redCube;

		//sceneRoot.appendChild(&model1);
		//sceneRoot.appendChild(&model2);
		

		Camera camera(window, drawingShader.id);		

		Core core(window, &camera, &sceneRoot, &drawingShader, &pickingShader);

		core.update(&loader.loadedNodes, transformInfo);
		TwTerminate();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}
