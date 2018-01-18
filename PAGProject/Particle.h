#pragma once
#include <glm/glm.hpp>

struct Particle {
	glm::vec3 pos, speed;
	unsigned char r, g, b, a; //color
	float size, angle, weight;
	float ttl = -1.0f; //time to live
	float cameraDistance;

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameraDistance > that.cameraDistance;
	}
};
