#include "SpotLight.h"


SpotLight::SpotLight(Shader* drawingShader, Shader* pickingShader) : GraphNode(drawingShader), pickingShader(pickingShader)
{
	position = glm::vec3(0.0f, 0.0f, 40.0f);
	cutoff = glm::cos(glm::radians(45.0f));
	attenuation = glm::vec3(1.0f, 0.02f, 0.0001f);
}

void SpotLight::render(Transform parentWorld)
{
	drawingShader->use();

	direction = -position;			// (0,0,0) - (m_position)

	drawingShader->setVec3("spotLight.ambient", getMaterial().ambient);
	drawingShader->setVec3("spotLight.diffuse", getMaterial().diffuse);
	drawingShader->setVec3("spotLight.specular", getMaterial().specular);
	drawingShader->setVec3("spotLight.att", attenuation);
	drawingShader->setVec3("spotLight.posWorld", position);
	drawingShader->setVec3("spotLight.direction", direction);
	drawingShader->setFloat("spotLight.cutoff", cutoff);

	GraphNode::render(local);
}

void SpotLight::renderForPicking(Transform parentWorld)
{

}

glm::vec3& SpotLight::getDirection()
{
	return direction;
}

glm::vec3& SpotLight::getAttenuation()
{
	return attenuation;
}

glm::vec3& SpotLight::getPosition()
{
	return position;
}

void SpotLight::setPosition(glm::vec3 v)
{
	position = v;
}