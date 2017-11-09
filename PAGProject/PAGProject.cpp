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
		
		GraphNode sceneRoot(NULL, program);

		CubeMesh* cubeMesh = new CubeMesh();
		cubeMesh->loadContent(0.5f, "Textures/trollface.jpg");

		SpinModificator* zSpinModificator = new SpinModificator(glm::vec3(0.0, 0.0, 1.0), 0.001f);
		SpinModificator* ySpinModificator = new SpinModificator(glm::vec3(0.0, 1.0, 0.0), 0.001f);

		GraphNode centerCube(cubeMesh, program);

		GraphNode zOrbit(NULL, program);
		zOrbit.local.modificator = zSpinModificator;

		GraphNode yOrbit(NULL, program);
		yOrbit.local.modificator = ySpinModificator;


		GraphNode orbitingMajorCube01(cubeMesh, program);
		Transform orbitingMajorCube01Transform;
		glm::mat4 trans(1.0f);
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
		trans = glm::translate(trans, glm::vec3(-5.0f, 0.0f, 0.0f));
		orbitingMajorCube01Transform.transformation = trans;
		orbitingMajorCube01.local = orbitingMajorCube01Transform;
		orbitingMajorCube01.local.modificator = ySpinModificator;

		GraphNode orbitingMinorCube01a(cubeMesh, program);
		Transform orbitingMinorCube01aTransform;
		glm::mat4 trans2(1.0f);
		trans2 = glm::scale(trans2, glm::vec3(0.5f, 0.5f, 0.5f));
		trans2 = glm::translate(trans2, glm::vec3(-3.0f, 0.0f, 0.0f));
		orbitingMinorCube01aTransform.transformation = trans2;
		orbitingMinorCube01a.local = orbitingMinorCube01aTransform;
		orbitingMinorCube01a.local.modificator = ySpinModificator;

		GraphNode orbitingMajorCube02(cubeMesh, program);
		Transform orbitingMajorCube02Transform;
		glm::mat4 trans3(1.0f);
		trans3 = glm::scale(trans3, glm::vec3(0.95f, 0.95f, 0.95f));
		trans3 = glm::translate(trans3, glm::vec3(3.0f, 4.0f, 0.0f));
		orbitingMajorCube02Transform.transformation = trans3;
		orbitingMajorCube02.local = orbitingMajorCube02Transform;
		orbitingMajorCube02.local.modificator = ySpinModificator;

		GraphNode orbitingMajorCube03(cubeMesh, program);
		Transform orbitingMajorCube03Transform;
		glm::mat4 trans4(1.0f);
		trans4 = glm::translate(trans4, glm::vec3(3.0f, 0.0f, 0.0f));
		orbitingMajorCube03Transform.transformation = trans4;
		orbitingMajorCube03.local = orbitingMajorCube03Transform;
		orbitingMajorCube03.local.modificator = zSpinModificator;


		orbitingMajorCube01.appendChild(&orbitingMinorCube01a);
		zOrbit.appendChild(&orbitingMajorCube01);
		zOrbit.appendChild(&orbitingMajorCube02);
		yOrbit.appendChild(&orbitingMajorCube03);
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