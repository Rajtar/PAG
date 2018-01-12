#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include "Window.h"
#include "Camera.h"
#include "InputHandler.h"
#include "ModelNode.h"
#include "Model.h"
#include <map>


class TransformInfo;

class Core
{
public:
	void update(std::map<int, ModelNode*>* nodes, TransformInfo* bindingTransform);
	void render();

	Core(Window* window, Camera* camera, ModelNode* graphRoot, Shader* drawingShader, Shader* pickingShader);
	~Core();

private:
	Window* window;
	Camera* camera;
	ModelNode* graphRoot;
	Shader* drawingShader;
	Shader* pickingShader;
	int alreadyFound = NULL;
	int pickedNodeId = 999999;

	bool doSwap = true;;

	int processPicking();
};

