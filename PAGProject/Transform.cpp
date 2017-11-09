#include "Transform.h"


Transform Transform::origin()
{
	Transform transform;
	transform.transformation = glm::mat4(1.0);

	return transform;
}

Transform Transform::combine(Transform & other)
{
	Transform combinedTransform;

	combinedTransform.transformation = other.transformation * this->transformation;

	return combinedTransform;
}

Transform::Transform()
{
}
