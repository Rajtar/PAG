#include "Material.h"


Material::Material()
{
	ambient = glm::vec3(1.f, 1.f, 1.f);
	diffuse = glm::vec3(1.f, 1.f, 1.f);
	specular = glm::vec3(1.f, 1.f, 1.f);
	specularFactor = 1.f;
}


void Material::SetSimple(Shader& shader)
{
	shader.setVec3("material.ambient", ambient);
	shader.setVec3("material.diffuse", diffuse);
	shader.setVec3("material.specular", specular);
	shader.setFloat("material.specFactor", specularFactor);
}
