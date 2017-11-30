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
#include <vector>
#include "Mesh.h"

class GraphNode
{
public:
	//GraphNode();
	//GraphNode(GLuint texture, Program* program) : texture(texture),local(Transform::origin()), program(program) {}
	void render(Transform parentWorld);
	void renderForPicking(Transform parentWorld);
	void appendChild(GraphNode* child);
	GraphNode(Shader* shader) : shader(shader) {};

	Transform local;
	std::vector<Mesh> meshes;
	std::vector<Texture> textures;
	Program* program;
	Shader* shader;
	unsigned int id;

//private:
	std::vector<GraphNode*> children;

};

