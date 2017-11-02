#include "GraphNode.h"

void GraphNode::render(Transform parentWorld)
{
	Transform world = local.combine(parentWorld);

	if (mesh) mesh->renderMesh();

	for (auto child: children)
	{
		child->render(parentWorld);
	}
}

void GraphNode::appendChild(GraphNode * child)
{
	children.push_back(child);
}
