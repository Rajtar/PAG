#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Particle.h"
#include "Shader.h"

class ParticlesEmitter
{
public:
	ParticlesEmitter(Shader* shader);

	void render(float delta);

private:

	const int maxParticles = 10000;
	Particle particles[10000];

	Shader* shader;

	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	GLuint billboard_vertex_buffer;

	int lastUsedParticle = 0;

	void initialize();

	int findUnusedParticle();
	void sortParticles();
};

