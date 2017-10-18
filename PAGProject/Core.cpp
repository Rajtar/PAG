#include "Core.h"
#include "InitializationException.cpp"

void Core::update()
{
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		render();

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


Core::Core(Window* window)
{
	this->window = window;
}

Core::~Core()
{
}
