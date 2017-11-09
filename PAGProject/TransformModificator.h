#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class TransformModificator
{
public:

	virtual glm::mat4 modifyTransformation(glm::mat4 transformation) = 0;

};