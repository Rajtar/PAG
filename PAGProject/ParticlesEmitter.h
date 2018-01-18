#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Particle.h"
#include "Shader.h"
#include "GraphNode.h"

class ParticlesEmitter : public GraphNode
{
public:
	ParticlesEmitter(Shader* shader);

	virtual void render(Transform parentWorld, float delta);
	virtual void renderForPicking(Transform parentWorld);

private:

	const int maxParticles = 10000;
	Particle particles[10000];

	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	GLuint billboard_vertex_buffer;

	int lastUsedParticle = 0;

	unsigned int texture;

	void initialize();
	void loadTexture();

	int findUnusedParticle();
	void sortParticles();
};

