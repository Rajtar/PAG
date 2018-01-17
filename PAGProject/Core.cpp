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
#include <exception>
#include "ModelLoader.h"

void Core::update(std::map<int, ModelNode*>* nodes, TransformInfo* bindingTransform, PointLight* orbitingLight)
{
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	ModelNode* currentNode = graphRoot;
	currentNode->id = 0;
	pickedNodeId = 0;

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera->reloadCamera();
		render();
		
		if(currentNode->id != pickedNodeId)
		{
			try
			{
				currentNode->isPicked = false;
				currentNode = nodes->at(pickedNodeId);
				currentNode->isPicked = true;

				std::cout << "CURRENT: " << currentNode->id << std::endl;

				bindingTransform->cloneValues(currentNode->transformInfo);
			}
			catch(...)
			{

			}

		}

		currentNode->transformInfo.cloneValues(*bindingTransform);
		
		

		InputHandler::processKeyboardInput(deltaTime, window);

		//HACK
		glm::vec3 pos;
		pos.y = 0.0f;
		pos.x = 100 * sinf(glfwGetTime() * 0.5);
		pos.z = 100 * cosf(glfwGetTime() * 0.5);
		orbitingLight->setPosition(pos);

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
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(InputHandler::pickingMode)
	{
		InputHandler::pickingMode = false;
		graphRoot->renderForPicking(Transform::origin());
		pickedNodeId = processPicking();

		doSwap = false;
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		graphRoot->render(Transform::origin());
		camera->reloadCamera();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		fullScreenQuad->drawQuad();
	}
}



Core::Core(Window* window, Camera* camera, ModelNode* graphRoot, Shader* drawingShader, Shader* pickingShader, unsigned int framebuffer, FullScreenQuad* fullScreenQuad)
{
	this->window = window;
	this->camera = camera;
	this->graphRoot = graphRoot;
	this->drawingShader = drawingShader;
	this->pickingShader = pickingShader;
	this->framebuffer = framebuffer;
	this->fullScreenQuad = fullScreenQuad;
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
