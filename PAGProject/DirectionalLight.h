#pragma once
#include "GraphNode.h"
#include "Material.h"

class DirectionalLight : public GraphNode
{
public:

	DirectionalLight(Shader* drawingShader, Shader* pickingShader);

	virtual void render(Transform parentWorld);
	virtual void renderForPicking(Transform parentWorld);

	glm::vec3& getDirection();
	void setDirection(glm::vec3 v);
	
private:
	Shader* pickingShader;
	glm::vec3 direction;
};

