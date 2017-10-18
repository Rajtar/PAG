#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Core.h"
#include "Window.h"
#include "Mesh.h"
#include "InitializationException.cpp"

int main()
{
	Window* window = new Window();
	Core core(window);
	Mesh mesh;

	try {

		window->init(620, 480);
		mesh.loadContent();
		core.update();
	}
	catch(InitializationException e) {
		
		std::cout << e.what() << std::endl;
	}
}