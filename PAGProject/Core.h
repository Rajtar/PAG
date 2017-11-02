#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include "Window.h"
#include "Camera.h"
#include "InputHandler.h"
#include "GraphNode.h"


class Core
{
public:
	void update();
	void render();

	Core(Window* window, Camera* camera, InputHandler* inputHandler, GraphNode* graphRoot);
	~Core();

private:
	Window* window;
	Camera* camera;
	InputHandler* inputHandler;
	GraphNode* graphRoot;
};

