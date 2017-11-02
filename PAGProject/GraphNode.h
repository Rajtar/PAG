#pragma once

#include "Transform.h"
#include "MeshBase.h"
#include <vector>

class GraphNode
{
public:
	GraphNode(MeshBase* mesh) : mesh(mesh), local(Transform::origin()) {}
	void render(Transform parentWorld);
	void appendChild(GraphNode* child);

//private:
	Transform local;
	MeshBase* mesh;

	std::vector<GraphNode*> children;
};

