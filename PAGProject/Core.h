#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include "Window.h"
#include "Renderable.h"

class Core
{
public:
	void update();
	void render();

	void addRenderable(Renderable* renderable);

	Core(Window* window);
	~Core();

private:
	Window* window;
	std::list<Renderable*> renderables;
};

