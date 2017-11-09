#include "GraphNode.h"

void GraphNode::render(Transform parentWorld)
{
	if (local.modificator) local.transformation = local.modificator->modifyTransformation(local.transformation);

	Transform world = local.combine(parentWorld);

	if (mesh)
	{
		mesh->renderMesh(&world, textureIndex);

		GLuint transformLoc = glGetUniformLocation(program->programHandle, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(world.transformation));
	}

	for (auto child: children)
	{
		child->render(world);
	}
}

void GraphNode::appendChild(GraphNode * child)
{
	children.push_back(child);
}
