#pragma once

#include "Transform.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Mesh.h"
#include "TransformInfo.h"
#include "GraphNode.h"

class ModelNode : public GraphNode
{
public:
	
	virtual void renderForPicking(Transform parentWorld);
	
	virtual void render(Transform parentWorld);
	ModelNode(Shader* drawingShader, Shader* pickingShader) : GraphNode(drawingShader), pickingShader(pickingShader) {};

	
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;

	Shader* pickingShader;
	int id;

	bool isPicked = false;
};

