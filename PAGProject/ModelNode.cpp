#include "ModelNode.h"
#include <iostream>

void ModelNode::render(Transform parentWorld)
{
	if (local.modificator) local.transformation = local.modificator->modifyTransformation(local.transformation);

	processTransformInfoChanges();

	Transform world = local.combine(parentWorld);

	GLuint transformLoc = glGetUniformLocation(drawingShader->id, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(world.transformation));

	float colors[4];

	if (isPicked)
	{
		colors[0] = 5.0f;
		colors[1] = 1.0f;
		colors[2] = 1.0f;
		colors[3] = 1.0f;

	}
	else
	{
		colors[0] = 1.0f;
		colors[1] = 1.0f;
		colors[2] = 1.0f;
		colors[3] = 1.0f;
	}

	GLuint colorModifierLoc = glGetUniformLocation(drawingShader->id, "colorModifier");
	glUniform4fv(colorModifierLoc, 1, colors);

	for(auto mesh: meshes)
	{
		mesh.draw(*drawingShader);
	}

	for (auto child: children)
	{
		child->render(world);
	}
}

void ModelNode::renderForPicking(Transform parentWorld)
{
	if (local.modificator) local.transformation = local.modificator->modifyTransformation(local.transformation);

	Transform world = local.combine(parentWorld);

	for (auto mesh : meshes)
	{
		GLuint transformLoc = glGetUniformLocation(pickingShader->id, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(world.transformation));

		float colors[4];

		colors[0] = 1.0f;
		colors[1] = 1.0f;
		colors[2] = 1.0f;
		colors[3] = 1.0f;

		GLuint colorModifierLoc = glGetUniformLocation(pickingShader->id, "colorModifier");
		glUniform4fv(colorModifierLoc, 1, colors);

		unsigned short r = (id & 0x000000FF) >> 0;
		unsigned short g = (id & 0x0000FF00) >> 8;
		unsigned short b = (id & 0x00FF0000) >> 16;

		GLuint pickingColorID = glGetUniformLocation(pickingShader->id, "PickingColor");
		glUniform4f(pickingColorID, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

		mesh.drawForPicking(*pickingShader);
	}

	for (auto child : children)
	{
		ModelNode* modelChild = (ModelNode*) child;
		modelChild->renderForPicking(world);
	}
}


