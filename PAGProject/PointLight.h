#pragma once
#include "GraphNode.h"
#include "Material.h"

class PointLight : public GraphNode
{
public:

	PointLight(Shader* drawingShader);;

	virtual void render(Transform parentWorld);

	glm::vec3 getPosition();
	void setPosition(glm::vec3 v);

	void setMaterial(Material* mat);

	glm::vec3 getAttenuation();


private:
	Material* material;
	glm::vec3 position;
	glm::vec3 attenuation;
};

