#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class TransformModificator
{
private:
	
	glm::vec3 transformationVector;

public:

	TransformModificator(glm::vec3 transformationVector);
	virtual glm::mat4 modifyTransformation(glm::mat4 transformation) = 0;
	glm::vec3 getTransformationVector();

};