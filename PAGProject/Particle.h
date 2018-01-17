#pragma once
#include <glm/glm.hpp>

struct Particle {
	glm::vec3 pos, speed;
	glm::vec4 color;
	float size, angle, weight;
	float ttl; // Time to live
	float cameraDistance;

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameraDistance > that.cameraDistance;
	}
};
