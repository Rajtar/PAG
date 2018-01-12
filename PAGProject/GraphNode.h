#pragma once
#include "Transform.h"
#include "Shader.h"
#include <vector>
#include "TransformInfo.h"

class GraphNode
{
public:

	std::vector<GraphNode*> children;
	Transform local;
	TransformInfo transformInfo;
	Shader* drawingShader;

	GraphNode(Shader* drawingShader) : drawingShader(drawingShader) {};


	void appendChild(GraphNode* child);
	virtual void render(Transform parentWorld) = 0{};

protected:

	void processTransformInfoChanges();

private:

	TransformInfo lastTransformInfo;
};
