#include "TransformModificator.h"

TransformModificator::TransformModificator(glm::vec3 transformationVector)
{
	this->transformationVector = transformationVector;
}

glm::vec3 TransformModificator::getTransformationVector()
{
	return transformationVector;
}
