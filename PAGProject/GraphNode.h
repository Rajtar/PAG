#pragma once
#include "Transform.h"
#include "Shader.h"
#include <vector>
#include "TransformInfo.h"
#include "Material.h"

class GraphNode
{
public:

	std::vector<GraphNode*> children;
	Transform local;
	TransformInfo transformInfo;
	Shader* drawingShader;

	GraphNode(Shader* drawingShader) : drawingShader(drawingShader) {};


	void appendChild(GraphNode* child);
	virtual void render(Transform parentWorld, float delta) = 0{};
	virtual void renderForPicking(Transform parentWorld) = 0 {};

	void setMaterial(Material mat);
	Material getMaterial();

protected:

	void processTransformInfoChanges();

private:
	Material material;
	TransformInfo lastTransformInfo;
};
