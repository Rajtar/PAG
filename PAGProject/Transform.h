#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
public:
	glm::mat4 transformation;
	

	static Transform origin();
	Transform combine(Transform& other);

	Transform();
};

