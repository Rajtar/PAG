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

//TODO: create GenericRenderer interface
void Core::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


Core::Core(Window* window)
{
	this->window = window;
}

Core::~Core()
{
}
