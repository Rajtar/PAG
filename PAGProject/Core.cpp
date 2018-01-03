#include "Core.h"
#include "Transform.h"
#include "InitializationException.cpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <AntTweakBar/AntTweakBar.h>
#include <iostream>
#include <sstream>
#include "TransformInfo.h"
#include "SpinModificator.h"

void Core::update(std::map<int, GraphNode*>* nodes, TransformInfo* bindingTransform)
{
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	GraphNode* currentNode = graphRoot;
	currentNode->id = 0;
	pickedNodeId = 0;

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		render();
		
		if(currentNode->id != pickedNodeId)
		{
			try
			{
				currentNode = nodes->at(pickedNodeId);
				std::cout << "CURRENT: " << currentNode->id << std::endl;

				bindingTransform->cloneValues(currentNode->transformInfo);
			}
			catch(...)
			{
				
			}

		}

		currentNode->transformInfo.cloneValues(*bindingTransform);
		
		camera->reloadCamera();

		InputHandler::processKeyboardInput(deltaTime, window);

		TwDraw();

		glfwPollEvents();

		if (doSwap)
			glfwSwapBuffers(window->getWindow());
		else
			doSwap = true;
	}

	glfwTerminate();
}

void Core::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(InputHandler::pickingMode)
	{
		InputHandler::pickingMode = false;
		graphRoot->renderForPicking(Transform::origin());
		pickedNodeId = processPicking();

		doSwap = false;
	}
	else
	{
		graphRoot->render(Transform::origin());
	}
}



Core::Core(Window* window, Camera* camera, GraphNode* graphRoot, Shader* drawingShader, Shader* pickingShader)
{
	this->window = window;
	this->camera = camera;
	this->graphRoot = graphRoot;
	this->drawingShader = drawingShader;
	this->pickingShader = pickingShader;
}

Core::~Core()
{
}

int Core::processPicking()
{
	glDisableVertexAttribArray(0);
	
	glFlush();
	glFinish();
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	unsigned char data[4];
	glReadPixels(1280 / 2, 720 / 2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
	
	unsigned short pickedID =
		data[0] +
		data[1] * 256 +
		data[2] * 256 * 256;
	

	std::cout << "PICKED: " << pickedID << std::endl;

	return pickedID;
}
