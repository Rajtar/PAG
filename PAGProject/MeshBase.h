#pragma once

#include "Transform.h"

class MeshBase {

public:
	virtual void renderMesh(Transform* transform) = 0;
};
