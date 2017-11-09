#include "SpinModificator.h"

glm::mat4 SpinModificator::modifyTransformation(glm::mat4 transformation)
{
	return transformation = glm::rotate(transformation, 0.0005f, glm::vec3(0.0, 0.0, 1.0));
}

SpinModificator::SpinModificator()
{
}


SpinModificator::~SpinModificator()
{
}
