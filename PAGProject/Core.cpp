#include "Core.h"
#include "Transform.h"
#include "InitializationException.cpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Core::update()
{
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window->getWindow()))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		render();

		camera->reloadCamera();

		inputHandler->processKeyboardInput(deltaTime);
		inputHandler->processMouseInput();

		/********************/
		//glm::mat4 trans;
		/*trans = glm::translate(trans, glm::vec3(0.0, 2.0, 0.0));
		trans = glm::rotate(trans, (GLfloat)glfwGetTime() * 2.0f, glm::vec3(1.0, 0.0, 0.0));
		trans = glm::translate(trans, glm::vec3(0.0, 2.0, 0.0));*/

		//GLuint transformLoc = glGetUniformLocation(camera->getProgram()->programHandle, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		/********************/

		glfwPollEvents();
		glfwSwapBuffers(window->getWindow());
	}

	glfwTerminate();
}

void Core::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	graphRoot->render(Transform::origin());
}

Core::Core(Window* window, Camera* camera, InputHandler* inputHandler, GraphNode* graphRoot)
{
	this->window = window;
	this->camera = camera;
	this->inputHandler = inputHandler;
	this->graphRoot = graphRoot;
}

Core::~Core()
{
}
