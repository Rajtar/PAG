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
#include "ModelNode.h"
#include "ModelLoader.h"
#include "Cube.h"
#include "SpinModificator.h"
#include <ctime>
#include <map>
#include "TransformInfo.h"
#include "Material.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Postprocess.h"


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
		Shader screenShader("Shaders/screen.vs", "Shaders/screen.fs");


		ModelNode sceneRoot(&drawingShader, &pickingShader);

		ModelNode model1(&drawingShader, &pickingShader);
		ModelNode model2(&drawingShader, &pickingShader);
		ModelNode planeModel(&drawingShader, &pickingShader);

		ModelNode redCube(&drawingShader, &pickingShader);
		ModelNode greenCube(&drawingShader, &pickingShader);
		ModelNode blueCube(&drawingShader, &pickingShader);


		ModelLoader loader;

		loader.loadModelOmmitingRoot("Models/CubeRed/CubeRed.obj", &redCube, &drawingShader, &pickingShader);
		loader.loadModelOmmitingRoot("Models/CubeGreen/CubeGreen.obj", &greenCube, &drawingShader, &pickingShader);
		loader.loadModelOmmitingRoot("Models/CubeBlue/CubeBlue.obj", &blueCube, &drawingShader, &pickingShader);

		loader.loadModel("Models/Spider-Man_Modern/Spider-Man_Modern.dae", &model2, &drawingShader, &pickingShader);

		loader.loadModel("Models/nanosuit/nanosuit.obj", &model1, &drawingShader, &pickingShader);

		loader.loadModel("Models/plane/plane.obj", &planeModel, &drawingShader, &pickingShader);
		


		//model2.local.transformation = glm::translate(model2.local.transformation, glm::vec3(0, 3.0, 0));
		//model2.local.transformation = glm::scale(model2.local.transformation, glm::vec3(0.01f, 0.01f, 0.01f));

		model2.local.transformation = glm::rotate(model2.local.transformation, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		model2.local.transformation = glm::translate(model2.local.transformation, glm::vec3(5.0f, 0.0f, 0.0f));


		redCube.local.transformation = glm::translate(redCube.local.transformation, glm::vec3(0, 3.0, 0));
		redCube.local.transformation = glm::scale(redCube.local.transformation, glm::vec3(0.01f, 0.01f, 0.01f));

		SpinModificator spin(glm::vec3(0.0f, 1.0f, 0.0f), 0.01);

		//redCube.local.modificator = &spin;

		greenCube.local.transformation = glm::translate(greenCube.local.transformation, glm::vec3(0.0, 0.0, 50.0));
		blueCube.local.transformation = glm::translate(blueCube.local.transformation, glm::vec3(00.0, 0.0, 50.0));

		//GraphNode test1(&drawingShader, &pickingShader);
		//Cube test1Cube(2.5f);
		//test1.meshes.push_back(Mesh(test1Cube.vertices, test1Cube.indices, std::vector<Texture>()));
		//test1.id = 1;
		//test1.local.modificator = &spin;

		//GraphNode test2(&drawingShader, &pickingShader);
		//Cube test2Cube(0.6f);
		//test2.meshes.push_back(Mesh(test2Cube.vertices, test2Cube.indices, std::vector<Texture>()));
		//test2.id = 2;
		//test2.local.transformation = glm::translate(test2.local.transformation, glm::vec3(0.0f, 5.0f, 0.0f));

		//GraphNode test3(&drawingShader, &pickingShader);
		//Cube test3Cube(0.3f);
		//test3.meshes.push_back(Mesh(test3Cube.vertices, test3Cube.indices, std::vector<Texture>()));
		//test3.id = 3;
		//test3.local.transformation = glm::translate(test3.local.transformation, glm::vec3(0.0f, 8.0f, 0.0f));

		//test2.appendChild(&test3);
		//test1.appendChild(&test2);
		//sceneRoot.appendChild(&test1);

		Material modelMaterial;

		modelMaterial.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		modelMaterial.specularFactor = 1;
		modelMaterial.SetSimple(drawingShader);

		model1.setMaterial(modelMaterial);
		model2.setMaterial(modelMaterial);
		redCube.setMaterial(modelMaterial);
		greenCube.setMaterial(modelMaterial);
		blueCube.setMaterial(modelMaterial);

		DirectionalLight directionalLight(&drawingShader, &pickingShader);
		Material matDirectional;
		matDirectional.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		matDirectional.diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
		matDirectional.specular = glm::vec3(0.3f, 0.3f, 0.3f);
		directionalLight.setMaterial(matDirectional);

		PointLight pointLight(&drawingShader, &pickingShader);

		Material matPoint;
		matPoint.specular = glm::vec3(0.05f, 0.05f, 0.05f);
		matPoint.ambient = glm::vec3(0.3f, 0.3f, 0.3f);
		matPoint.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		pointLight.setMaterial(matPoint);

		SpotLight spotLight(&drawingShader, &pickingShader);
		Material matSpot;
		matSpot.ambient = matSpot.specular = matSpot.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		spotLight.setMaterial(matSpot);

		sceneRoot.appendChild(&directionalLight);
		sceneRoot.appendChild(&pointLight);
		sceneRoot.appendChild(&spotLight);


		sceneRoot.appendChild(&model1);
		sceneRoot.appendChild(&model2);
		sceneRoot.appendChild(&planeModel);

		redCube.appendChild(&greenCube);
		greenCube.appendChild(&blueCube);
		sceneRoot.appendChild(&redCube);	

		Camera camera(window, drawingShader.id);		

		Postprocess postprocess;
		FullScreenQuad quad(&screenShader, postprocess.textureColorBuffer);

		Core core(window, &camera, &sceneRoot, &drawingShader, &pickingShader, postprocess.framebuffer, &quad);



		/*****************/
		TwBar *barLighting = TwNewBar("Lighting");
		TwDefine(" Lighting position='15 350' ");
		TwAddVarRW(barLighting, "Direction", TW_TYPE_DIR3F, &directionalLight.getDirection(), "Group=Directional");

		TwAddVarRW(barLighting, "AttenuationConst", TW_TYPE_FLOAT, &pointLight.getAttenuation().x, "Group=Point");
		TwAddVarRW(barLighting, "AttenuationLinear", TW_TYPE_FLOAT, &pointLight.getAttenuation().y, "Group=Point step=0.001 min=0");
		TwAddVarRW(barLighting, "AttenuationQuadratic", TW_TYPE_FLOAT, &pointLight.getAttenuation().z, "Group=Point step=0.0001 min=0");

		//TwAddVarRW(barLighting, "SpotDirection", TW_TYPE_DIR3F, &spotLight.getDirection(), "Group=Spot");
		TwAddVarRW(barLighting, "Position", TW_TYPE_DIR3F, &spotLight.getPosition(), "Group=Spot");
		/*****************/

		/**************************/
		float cubeVertices[] = {
			// positions          // texture Coords
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		unsigned int cubeVAO, cubeVBO;
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		core.cubeVAO = cubeVAO;
		/**************************/



		core.update(&loader.loadedNodes, transformInfo, &pointLight);
		TwTerminate();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}
