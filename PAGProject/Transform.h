#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "TransformModificator.h"

class Transform
{
public:
	glm::mat4 transformation;

	TransformModificator* modificator = NULL;

	static Transform origin();
	Transform combine(Transform& other);

	Transform();
};

