#include "DirectionalLight.h"


void DirectionalLight::render(Transform parentWorld)
{
	drawingShader->use();

	drawingShader->setVec3("dirLight.ambient", material->ambient);
	drawingShader->setVec3("dirLight.diffuse", material->diffuse);
	drawingShader->setVec3("dirLight.specular", material->specular);
	drawingShader->setVec3("dirLight.direction", direction);

	GraphNode::render(local);
}

DirectionalLight::DirectionalLight(Shader* drawingShader): GraphNode(drawingShader)
{
	direction = glm::vec3(0.f, -1.f, 0.f);
}

glm::vec3 DirectionalLight::getDirection()
{
	return direction;
}

void DirectionalLight::setDirection(glm::vec3 v)
{
	this->direction = v;
}

void DirectionalLight::setMaterial(Material* mat)
{
	this->material = mat;
}
