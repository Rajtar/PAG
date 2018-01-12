#pragma once
#include "GraphNode.h"
#include "Material.h"

class DirectionalLight : public GraphNode
{
public:

	DirectionalLight(Shader* drawingShader);;

	virtual void render(Transform parentWorld);

	glm::vec3 getDirection();
	void setDirection(glm::vec3 v);

	void setMaterial(Material* mat);
	
private:
	Material* material;
	glm::vec3 direction;
};

