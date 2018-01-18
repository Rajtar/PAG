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

	int& getRefParticlesForPass();
	float& getRefTtlToSet();
	float& getRefSpread();
	float& getRefSizeRate();
	float& getRefAlphaChannel();
	glm::vec3& getRefMainDirection();

private:
	const int maxParticles = 10000;
	Particle particles[10000];

	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	GLuint billboard_vertex_buffer;

	int lastUsedParticle = 0;

	unsigned int texture;

	/*****GUI BINDS*****/
	int particlesForPass = 100;
	float ttlToSet = 1.0f;
	float spread = 2.0f;
	float sizeRate = 2000.0f;
	float alphaChannel = 0.03f;
	glm::vec3 mainDirection = glm::vec3(0.0f, 10.0f, 0.0f);
	/*******************/

	void initialize();
	void loadTexture();

	int findUnusedParticle();
	void sortParticles();
};

