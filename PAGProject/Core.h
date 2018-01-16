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
#include "PointLight.h"
#include "FullScreenQuad.h"


class TransformInfo;

class Core
{
public:
	void update(std::map<int, ModelNode*>* nodes, TransformInfo* bindingTransform, PointLight* orbitingLight);
	void render();

	Core(Window* window, Camera* camera, ModelNode* graphRoot, Shader* drawingShader, Shader* pickingShader, unsigned int framebuffer, FullScreenQuad* fullScreenQuad);
	~Core();

	unsigned int cubeVAO;

private:
	Window* window;
	Camera* camera;
	ModelNode* graphRoot;
	Shader* drawingShader;
	Shader* pickingShader;
	int alreadyFound = NULL;
	int pickedNodeId = 999999;

	bool doSwap = true;

	unsigned int framebuffer;
	FullScreenQuad* fullScreenQuad;

	int processPicking();
};

