#pragma once
#include "GraphNode.h"
#include "Material.h"
class SpotLight : public GraphNode
{
public:

	SpotLight(Shader* drawingShader, Shader* pickingShader);

	virtual void render(Transform parentWorld, float delta);
	virtual void renderForPicking(Transform parentWorld);


	glm::vec3& getDirection();
	glm::vec3& getAttenuation();
	glm::vec3& getPosition();
	void setPosition(glm::vec3 v);

private:
	Shader* pickingShader;
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 attenuation;
	float cutoff;
};

