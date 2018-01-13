#include "DirectionalLight.h"


void DirectionalLight::render(Transform parentWorld)
{
	drawingShader->use();

	drawingShader->setVec3("dirLight.ambient", getMaterial().ambient);
	drawingShader->setVec3("dirLight.diffuse", getMaterial().diffuse);
	drawingShader->setVec3("dirLight.specular", getMaterial().specular);
	drawingShader->setVec3("dirLight.direction", direction);

	GraphNode::render(local);
}

void DirectionalLight::renderForPicking(Transform parentWorld)
{

}

DirectionalLight::DirectionalLight(Shader* drawingShader): GraphNode(drawingShader)
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

glm::vec3& DirectionalLight::getDirection()
{
	return direction;
}

void DirectionalLight::setDirection(glm::vec3 v)
{
	this->direction = v;
}
