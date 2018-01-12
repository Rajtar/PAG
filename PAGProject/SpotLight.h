#pragma once
#include "GraphNode.h"
#include "Material.h"
class SpotLight : public GraphNode
{
public:

	SpotLight(Shader* drawingShader);;

	virtual void render(Transform parentWorld);

	glm::vec3 getDirection();
	glm::vec3 getAttenuation();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 v);

	void setMaterial(Material* mat);

private:
	Material* material;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 attenuation;
	float cutoff;
};

