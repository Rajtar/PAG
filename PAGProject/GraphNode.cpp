#include "GraphNode.h"
#include <iostream>

void GraphNode::render(Transform parentWorld)
{
	if (local.modificator) local.transformation = local.modificator->modifyTransformation(local.transformation);

	processTransformInfoChanges();

	Transform world = local.combine(parentWorld);

	/*if (mesh)
	{
		mesh->renderMesh(&world, texture);

		GLuint transformLoc = glGetUniformLocation(program->programHandle, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(world.transformation));
	}*/

	for(auto mesh: meshes)
	{
		mesh.draw(*drawingShader);

		GLuint transformLoc = glGetUniformLocation(drawingShader->id, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(world.transformation));
	}

	for (auto child: children)
	{
		child->render(world);
	}
}

void GraphNode::renderForPicking(Transform parentWorld)
{
	if (local.modificator) local.transformation = local.modificator->modifyTransformation(local.transformation);

	Transform world = local.combine(parentWorld);

	for (auto mesh : meshes)
	{
		mesh.drawForPicking(*pickingShader);

		unsigned short r = (id & 0x000000FF) >> 0;
		unsigned short g = (id & 0x0000FF00) >> 8;
		unsigned short b = (id & 0x00FF0000) >> 16;

		GLuint pickingColorID = glGetUniformLocation(pickingShader->id, "PickingColor");
		glUniform4f(pickingColorID, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

		GLuint transformLoc = glGetUniformLocation(pickingShader->id, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(world.transformation));
	}

	for (auto child : children)
	{
		child->renderForPicking(world);
	}
}

void GraphNode::appendChild(GraphNode * child)
{
	children.push_back(child);
}

void GraphNode::processTransformInfoChanges()
{
	TransformInfo transformToApply = transformInfo - lastTransformInfo;

	lastTransformInfo = transformInfo;

	local.transformation = glm::translate(local.transformation, glm::vec3(transformToApply.translateX, transformToApply.translateY, transformToApply.translateZ));

	if(transformToApply.rotateX != 0 || transformToApply.rotateY != 0 || transformToApply.rotateZ != 0)
		local.transformation = glm::rotate(local.transformation, transformToApply.rotateAngle, glm::vec3(transformToApply.rotateX, transformToApply.rotateY, transformToApply.rotateZ));
	
	if (transformToApply.scaleX != 0 && transformToApply.scaleY != 0 && transformToApply.scaleZ != 0)
		local.transformation = glm::scale(local.transformation, glm::vec3(transformToApply.scaleX, transformToApply.scaleY, transformToApply.scaleZ));
}

