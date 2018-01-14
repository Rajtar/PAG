#pragma once
#include "GraphNode.h"
#include "Material.h"

class PointLight : public GraphNode
{
public:

	PointLight(Shader* drawingShader, Shader* pickingShader);

	virtual void render(Transform parentWorld);
	virtual void renderForPicking(Transform parentWorld);


	glm::vec3 getPosition();
	void setPosition(glm::vec3 v);

	glm::vec3& getAttenuation();


private:
	Shader* pickingShader;
	glm::vec3 position;
	glm::vec3 attenuation;
};

