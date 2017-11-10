#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
#include "Transform.h"
#include "SpinModificator.h"
#include "OrbitModificator.h"
#include "Texture.h"

void buildSceneGraph(Program*, GraphNode&);

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
		
		GraphNode sceneRoot(NULL, 0, program);

		CubeMesh* cubeMesh = new CubeMesh();
		cubeMesh->loadContent(0.5f);

		Texture trollTexture;
		trollTexture.loadTexture("Textures/trollface.jpg");

		Texture woodTexture;
		woodTexture.loadTexture("Textures/wood.jpg");

		Texture grassTexture;
		grassTexture.loadTexture("Textures/grass.jpg");

		Texture sunTexture;
		sunTexture.loadTexture("Textures/sun.jpg");

		Texture dogeTexture;
		dogeTexture.loadTexture("Textures/doge.png");

		cubeMesh->addTexture(trollTexture.getTextureHolder());
		cubeMesh->addTexture(woodTexture.getTextureHolder());
		cubeMesh->addTexture(grassTexture.getTextureHolder());
		cubeMesh->addTexture(sunTexture.getTextureHolder());
		cubeMesh->addTexture(dogeTexture.getTextureHolder());

		SpinModificator* xSpinModificator = new SpinModificator(glm::vec3(1.0, 0.0, 0.0), 0.002f);
		SpinModificator* ySpinModificator = new SpinModificator(glm::vec3(0.0, 1.0, 0.0), 0.003f);
		SpinModificator* zSpinModificator = new SpinModificator(glm::vec3(0.0, 0.0, 1.0), 0.001f);

		GraphNode xOrbit(NULL, 0, program);
		xOrbit.local.modificator = xSpinModificator;

		GraphNode yOrbit(NULL, 0, program);
		yOrbit.local.modificator = ySpinModificator;

		GraphNode zOrbit(NULL, 0, program);
		zOrbit.local.modificator = zSpinModificator;

		GraphNode centerCube(cubeMesh, 0, program);
		centerCube.local.modificator = ySpinModificator;

		GraphNode orbitingMajorCube01(cubeMesh, 1, program);
		Transform orbitingMajorCube01Transform;
		glm::mat4 trans(1.0f);
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
		trans = glm::translate(trans, glm::vec3(-5.0f, 0.0f, 0.0f));
		orbitingMajorCube01Transform.transformation = trans;
		orbitingMajorCube01.local = orbitingMajorCube01Transform;
		orbitingMajorCube01.local.modificator = ySpinModificator;

		GraphNode orbitingMinorCube01a(cubeMesh, 2, program);
		Transform orbitingMinorCube01aTransform;
		glm::mat4 trans2(1.0f);
		trans2 = glm::scale(trans2, glm::vec3(0.5f, 0.5f, 0.5f));
		trans2 = glm::translate(trans2, glm::vec3(-3.0f, 0.0f, 0.0f));
		orbitingMinorCube01aTransform.transformation = trans2;
		orbitingMinorCube01a.local = orbitingMinorCube01aTransform;
		orbitingMinorCube01a.local.modificator = ySpinModificator;
		
		GraphNode orbitingMajorCube02(cubeMesh, 0, program);
		Transform orbitingMajorCube02Transform;
		glm::mat4 trans3(1.0f);
		trans3 = glm::scale(trans3, glm::vec3(0.95f, 0.95f, 0.95f));
		trans3 = glm::translate(trans3, glm::vec3(3.0f, 4.0f, 0.0f));
		orbitingMajorCube02Transform.transformation = trans3;
		orbitingMajorCube02.local = orbitingMajorCube02Transform;
		orbitingMajorCube02.local.modificator = ySpinModificator;

		GraphNode orbitingMajorCube03(cubeMesh, 1, program);
		Transform orbitingMajorCube03Transform;
		glm::mat4 trans4(1.0f);
		trans4 = glm::scale(trans4, glm::vec3(0.9f, 0.9f, 0.9f));
		trans4 = glm::translate(trans4, glm::vec3(3.0f, 0.0f, 0.0f));
		orbitingMajorCube03Transform.transformation = trans4;
		orbitingMajorCube03.local = orbitingMajorCube03Transform;
		orbitingMajorCube03.local.modificator = zSpinModificator;

		GraphNode orbitingMajorCube04(cubeMesh, 2, program);
		Transform orbitingMajorCube04Transform;
		glm::mat4 trans5(1.0f);
		trans5 = glm::scale(trans5, glm::vec3(0.6f, 0.6f, 0.6f));
		trans5 = glm::translate(trans5, glm::vec3(3.0f, 0.0f, 6.0f));
		orbitingMajorCube04Transform.transformation = trans5;
		orbitingMajorCube04.local = orbitingMajorCube04Transform;
		orbitingMajorCube04.local.modificator = zSpinModificator;

		GraphNode orbitingMajorCube05(cubeMesh, 0, program);
		Transform orbitingMajorCube05Transform;
		glm::mat4 trans6(1.0f);
		trans6 = glm::scale(trans6, glm::vec3(0.3f, 0.3f, 0.3f));
		trans6 = glm::translate(trans6, glm::vec3(-3.0f, 0.0f, 6.0f));
		orbitingMajorCube05Transform.transformation = trans6;
		orbitingMajorCube05.local = orbitingMajorCube05Transform;
		orbitingMajorCube05.local.modificator = zSpinModificator;

		GraphNode orbitingMajorCube06(cubeMesh, 4, program);
		Transform orbitingMajorCube06Transform;
		glm::mat4 trans7(1.0f);
		trans7 = glm::scale(trans7, glm::vec3(0.3f, 0.3f, 0.3f));
		trans7 = glm::translate(trans7, glm::vec3(0.0f, -3.0f, 6.0f));
		orbitingMajorCube06Transform.transformation = trans7;
		orbitingMajorCube06.local = orbitingMajorCube06Transform;
		orbitingMajorCube06.local.modificator = zSpinModificator;

		GraphNode orbitingMajorCube07(cubeMesh, 2, program);
		Transform orbitingMajorCube07Transform;
		glm::mat4 trans8(1.0f);
		trans8 = glm::scale(trans8, glm::vec3(1.2f, 1.2f, 1.2f));
		trans8 = glm::translate(trans8, glm::vec3(0.0f, 3.0f, -6.0f));
		orbitingMajorCube07Transform.transformation = trans8;
		orbitingMajorCube07.local = orbitingMajorCube07Transform;
		orbitingMajorCube07.local.modificator = ySpinModificator;

		GraphNode orbitingMinorCube07a(cubeMesh, 0, program);
		Transform orbitingMinorCube07aTransform;
		glm::mat4 trans9(1.0f);
		trans9 = glm::scale(trans9, glm::vec3(0.6f, 0.6f, 0.6f));
		trans9 = glm::translate(trans9, glm::vec3(0.0f, 3.0f, -6.0f));
		orbitingMinorCube07aTransform.transformation = trans9;
		orbitingMinorCube07a.local = orbitingMinorCube07aTransform;
		orbitingMinorCube07a.local.modificator = zSpinModificator;


		orbitingMajorCube01.appendChild(&orbitingMinorCube01a);
		orbitingMajorCube07.appendChild(&orbitingMinorCube07a);
		zOrbit.appendChild(&orbitingMajorCube01);
		zOrbit.appendChild(&orbitingMajorCube02);
		yOrbit.appendChild(&orbitingMajorCube03);
		yOrbit.appendChild(&orbitingMajorCube04);
		yOrbit.appendChild(&orbitingMajorCube05);
		xOrbit.appendChild(&orbitingMajorCube06);
		xOrbit.appendChild(&orbitingMajorCube07);
		sceneRoot.appendChild(&xOrbit);
		sceneRoot.appendChild(&yOrbit);
		sceneRoot.appendChild(&zOrbit);
		sceneRoot.appendChild(&centerCube);

		Core core(window, cameraPtr, inputHandler, &sceneRoot);

		core.update();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}

void buildSceneGraph(Program* program, GraphNode& sceneRoot)
{

}