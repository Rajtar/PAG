#include "TransformInfo.h"

void TransformInfo::cloneValues(TransformInfo other)
{
	translateX = other.translateX;
	translateY = other.translateY;
	translateZ = other.translateZ;

	rotateX = other.rotateX;
	rotateY = other.rotateY;
	rotateZ = other.rotateZ;
	rotateAngle = other.rotateAngle;

	scaleX = other.scaleX;
	scaleY = other.scaleY;
	scaleZ = other.scaleZ;
}

TransformInfo TransformInfo::operator-(TransformInfo other)
{
	TransformInfo newTransform;

	newTransform.translateX = this->translateX - other.translateX;
	newTransform.translateY = this->translateY - other.translateY;
	newTransform.translateZ = this->translateZ - other.translateZ;
	
	newTransform.rotateX = this->rotateX;
	newTransform.rotateY = this->rotateY;
	newTransform.rotateZ = this->rotateZ;
	newTransform.rotateAngle = this->rotateAngle - other.rotateAngle;
	
	if (this->scaleX == other.scaleX)
		newTransform.scaleX = 1;
	else
	{
		newTransform.scaleX = 1 - (other.scaleX - this->scaleX);
	}

	if (this->scaleY == other.scaleY)
		newTransform.scaleY = 1;
	else
	{
		newTransform.scaleY = 1 - (other.scaleY - this->scaleY);
	}

	if (this->scaleZ == other.scaleZ)
		newTransform.scaleZ = 1;
	else
	{
		newTransform.scaleZ = 1 - (other.scaleZ - this->scaleZ);
	}

	return newTransform;
}
