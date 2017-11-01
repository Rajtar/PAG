#include "Core.h"
#include "InitializationException.cpp"

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

		keyboardHandler->processInput(deltaTime);

		glfwPollEvents();
		glfwSwapBuffers(window->getWindow());
	}

	glfwTerminate();
}

void Core::render()
{
	for (auto &renderable : renderables)
	{
		renderable->render();
	}
}

void Core::addRenderable(Renderable* renderable)
{
	renderables.push_back(renderable);
}


Core::Core(Window* window, Camera* camera, KeyboardHandler* keyboardHandler)
{
	this->window = window;
	this->camera = camera;
	this->keyboardHandler = keyboardHandler;
}

Core::~Core()
{
}
