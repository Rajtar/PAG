#pragma once
#include <glm/detail/type_vec3.hpp>

#include "Shader.h"

class Material
{
public:

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float specularFactor;
	
	Material();
	void SetSimple(Shader& shader);
};

