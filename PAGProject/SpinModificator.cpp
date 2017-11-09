#include "SpinModificator.h"

glm::mat4 SpinModificator::modifyTransformation(glm::mat4 transformation)
{
	return transformation = glm::rotate(transformation, spinAngle, getTransformationVector());
}

GLfloat SpinModificator::getSpinAngle()
{
	return spinAngle;
}

SpinModificator::SpinModificator(glm::vec3 transformationVector, GLfloat spinAngle) : TransformModificator(transformationVector), spinAngle(spinAngle)
{

}


SpinModificator::~SpinModificator()
{
}
