#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include "Window.h"
#include "Camera.h"
#include "InputHandler.h"
#include "GraphNode.h"
#include "Model.h"
#include <map>


class Core
{
public:
	void update(std::map<int, GraphNode*>* nodes);
	void render();

	Core(Window* window, Camera* camera, GraphNode* graphRoot, Shader* drawingShader, Shader* pickingShader);
	~Core();

private:
	Window* window;
	Camera* camera;
	GraphNode* graphRoot;
	Shader* drawingShader;
	Shader* pickingShader;
	int alreadyFound = NULL;
	int pickedNodeId = 999999;

	int processPicking();
};

