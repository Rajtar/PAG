#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include "Window.h"
#include "Renderable.h"
#include "Camera.h"
#include "KeyboardHandler.h"

class Core
{
public:
	void update();
	void render();

	void addRenderable(Renderable* renderable);

	Core(Window* window, Camera* camera, KeyboardHandler* keyboardHandler);
	~Core();

private:
	Window* window;
	Camera* camera;
	KeyboardHandler* keyboardHandler;
	std::list<Renderable*> renderables;
};

