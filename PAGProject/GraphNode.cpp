#include "GraphNode.h"

void GraphNode::render(Transform parentWorld)
{
	if (local.modificator) local.transformation = local.modificator->modifyTransformation(local.transformation);

	Transform world = local.combine(parentWorld);

	/*if (mesh)
	{
		mesh->renderMesh(&world, texture);

		GLuint transformLoc = glGetUniformLocation(program->programHandle, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(world.transformation));
	}*/

	for(auto mesh: meshes)
	{
		mesh.draw(*shader);

		GLuint transformLoc = glGetUniformLocation(shader->id, "transform");
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
		GLuint transformLoc = glGetUniformLocation(shader->id, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(world.transformation));

		int r = (id & 0x000000FF) >> 0;
		int g = (id & 0x0000FF00) >> 8;
		int b = (id & 0x00FF0000) >> 16;

		GLuint pickingColorID = glGetUniformLocation(shader->id, "PickingColor");
		glUniform4f(pickingColorID, r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
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
