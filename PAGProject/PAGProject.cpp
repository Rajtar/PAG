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
		
		CubeMesh* cubeMesh = new CubeMesh();
		cubeMesh->loadContent(0.5f, "Textures/trollface.jpg");
		
		GraphNode sceneRoot(NULL, program);

		SpinModificator* spinModificator = new SpinModificator();
		OrbitModificator* orbitModificator = new OrbitModificator();


		GraphNode centerCube(cubeMesh, program);

		centerCube.local.modificator = spinModificator;
		
		GraphNode orbitingMajorCube01(cubeMesh, program);
		Transform orbitingMajorCube01Transform;
		glm::mat4 trans(1.0f);
		trans = glm::translate(trans, glm::vec3(-2.0f, 0.0f, 0.0f));
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
		orbitingMajorCube01Transform.transformation = trans;
		orbitingMajorCube01.local = orbitingMajorCube01Transform;
		//orbitingMajorCube01.local.modificator = orbitModificator;

		//GraphNode orbitingMinorCube01a(cubeMesh, program);
		//Transform orbitingMinorCube01aTransform;
		//glm::mat4 trans2(1.0f);
		//orbitingMinorCube01aTransform.transformation = trans2;
		//orbitingMinorCube01a.local = orbitingMinorCube01aTransform;

		//orbitingMajorCube01.appendChild(&orbitingMinorCube01a);
		
		centerCube.appendChild(&orbitingMajorCube01);
		sceneRoot.appendChild(&centerCube);
		

		Core core(window, cameraPtr, inputHandler, &sceneRoot);

		

		core.update();
	}
	catch (InitializationException e) {

		std::cout << e.what() << std::endl;
	}
}