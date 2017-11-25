#pragma once

#include "Transform.h"
#include "Program.h"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"

class GraphNode
{
public:
	GraphNode(Mesh* mesh, GLuint texture, Program* program) : mesh(mesh), texture(texture),local(Transform::origin()), program(program) {}
	void render(Transform parentWorld);
	void appendChild(GraphNode* child);

//private:
	Transform local;
	Mesh* mesh;
	Program* program;

private:
	std::vector<GraphNode*> children;
	GLuint texture;

};

