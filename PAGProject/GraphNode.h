#pragma once

#include "Transform.h"
#include "MeshBase.h"
#include "Program.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GraphNode
{
public:
	GraphNode(MeshBase* mesh, Program* program) : mesh(mesh), local(Transform::origin()), program(program) {}
	void render(Transform parentWorld);
	void appendChild(GraphNode* child);

//private:
	Transform local;
	MeshBase* mesh;
	Program* program;

	std::vector<GraphNode*> children;
};

