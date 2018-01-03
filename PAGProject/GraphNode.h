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

class GraphNode
{
public:
	void render(Transform parentWorld);
	void renderForPicking(Transform parentWorld);
	void appendChild(GraphNode* child);

	GraphNode(Shader* drawingShader, Shader* pickingShader) : drawingShader(drawingShader), pickingShader(pickingShader) {};

	Transform local;
	TransformInfo transformInfo;
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
	Shader* drawingShader;
	Shader* pickingShader;
	int id;

	bool isPicked = false;

//private:
	std::vector<GraphNode*> children;

private:
	TransformInfo lastTransformInfo;

	void processTransformInfoChanges();

};

