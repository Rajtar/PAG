#pragma once
class TransformInfo
{
public:
	
	float translateX = 0;
	float translateY = 0;
	float translateZ = 0;
	
	float rotateX = 0;
	float rotateY = 0;
	float rotateZ = 0;
	float rotateAngle = 0;
	
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	float scaleZ = 1.0f;

	void cloneValues(TransformInfo other);

	TransformInfo operator-(TransformInfo other);
};

