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

		srand(time(NULL));

		int windowWidth, windowHeight;

		/*windowWidth = 1280;
		windowHeight = 720;*/

		windowWidth = 800;
		windowHeight = 600;

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
		GraphNode model3(&drawingShader, &pickingShader);

		sceneRoot.appendChild(&model1);
		sceneRoot.appendChild(&model2);
		sceneRoot.appendChild(&model3);

		ModelLoader loader;

		loader.loadModel("Models/nanosuit/nanosuit.obj", &model1, &drawingShader, &pickingShader);
		//loader.loadModel("Models/human/human.blend", &sceneRoot, &ourShader);
		
		loader.loadModel("Models/Spider-Man_Modern/Spider-Man_Modern.dae", &model1, &drawingShader, &pickingShader);

		loader.loadModel("Models/ironman/Iron_Man.dae", &model3, &drawingShader, &pickingShader);
		//loader.loadModel("Models/shapes/shapes.FBX", &sceneRoot, &ourShader);


		SpinModificator spin(glm::vec3(0.0f, 1.0f, 0.0f), 0.005f);

		Transform t;
		//t.modificator = &spin;
		//t.transformation = glm::translate(t.transformation, glm::vec3(0, 3.0, 0));
		//t.transformation = glm::scale(t.transformation, glm::vec3(0.01f, 0.01f, 0.01f));

		//sceneRoot.children[2]->local = t;

		Camera camera(window, drawingShader.id);

		Camera* cameraPtr = &camera;
		

		Core core(window, cameraPtr, &sceneRoot, &drawingShader, &pickingShader);

		core.update(&loader.loadedNodes, transformInfo);
		TwTerminate();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}
