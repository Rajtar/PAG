#include "PointLight.h"



void PointLight::render(Transform parentWorld)
{
	drawingShader->use();

	drawingShader->setVec3("pointLight.ambient", material->ambient);
	drawingShader->setVec3("pointLight.diffuse", material->diffuse);
	drawingShader->setVec3("pointLight.specular", material->specular);
	drawingShader->setVec3("pointLight.posWorld", position);
	drawingShader->setVec3("pointLight.att", attenuation);

	GraphNode::render(local);
}

PointLight::PointLight(Shader* drawingShader): GraphNode(drawingShader)
{
	attenuation = glm::vec3(0.2f, 0.001f, 0.0001f);
}

glm::vec3 PointLight::getPosition()
{
	return position;
}

void PointLight::setPosition(glm::vec3 v)
{
	position = v;
}

void PointLight::setMaterial(Material* mat)
{
	material = mat;
}

glm::vec3 PointLight::getAttenuation()
{
	return attenuation;
}
