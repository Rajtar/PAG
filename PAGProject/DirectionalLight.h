#pragma once
#include "GraphNode.h"
#include "Material.h"

class DirectionalLight : public GraphNode
{
public:

	DirectionalLight(Shader* drawingShader);;

	virtual void render(Transform parentWorld);
	virtual void renderForPicking(Transform parentWorld);

	glm::vec3& getDirection();
	void setDirection(glm::vec3 v);
	
private:
	glm::vec3 direction;
};

