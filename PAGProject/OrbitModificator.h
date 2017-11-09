#pragma once
#include "TransformModificator.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class OrbitModificator : public TransformModificator
{
public:

	virtual glm::mat4 modifyTransformation(glm::mat4 transformation);

	OrbitModificator();
	~OrbitModificator();
};

