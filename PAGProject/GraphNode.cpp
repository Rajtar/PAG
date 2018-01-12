#include "GraphNode.h"

void GraphNode::appendChild(GraphNode * child)
{
	children.push_back(child);
}

void GraphNode::processTransformInfoChanges()
{
	TransformInfo transformToApply = transformInfo - lastTransformInfo;

	lastTransformInfo = transformInfo;

	local.transformation = glm::translate(local.transformation, glm::vec3(transformToApply.translateX, transformToApply.translateY, transformToApply.translateZ));

	if (transformToApply.rotateX != 0 || transformToApply.rotateY != 0 || transformToApply.rotateZ != 0)
		local.transformation = glm::rotate(local.transformation, transformToApply.rotateAngle, glm::vec3(transformToApply.rotateX, transformToApply.rotateY, transformToApply.rotateZ));

	if (transformToApply.scaleX != 0 && transformToApply.scaleY != 0 && transformToApply.scaleZ != 0)
		local.transformation = glm::scale(local.transformation, glm::vec3(transformToApply.scaleX, transformToApply.scaleY, transformToApply.scaleZ));
}