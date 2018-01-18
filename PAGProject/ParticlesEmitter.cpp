#include "ParticlesEmitter.h"
#include "InputHandler.h"
#include <stb_image.h>
#include <iostream>


ParticlesEmitter::ParticlesEmitter(Shader* shader)
{
	this->shader = shader;

	loadTexture();
	initialize();
}

void ParticlesEmitter::render(float delta)
{
	int a = 0;

	GLfloat* particles_position_size_data = new GLfloat[maxParticles * 4];
	GLubyte* particles_color_data = new GLubyte[maxParticles * 4];



	int newParticles = (int)(delta*10000.0);
	if (newParticles > (int)(0.016f*10000.0))
		newParticles = (int)(0.016f*10000.0);

	newParticles = 100;

	for (int i = 0; i<newParticles; i++) {
		int particleIndex = findUnusedParticle();

		particles[particleIndex].ttl = 0.5f; // This particle will live 5 seconds.
		particles[particleIndex].pos = glm::vec3(0, 0, -20.0f);

		float spread = 1.5f;
		glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);
		// Very bad way to generate a random direction; 
		// See for instance http://stackoverflow.com/questions/5408276/python-uniform-spherical-distribution instead,
		// combined with some user-controlled parameters (main direction, spread, etc)
		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);

		particles[particleIndex].speed = maindir + randomdir*spread;

		particles[particleIndex].color = glm::vec4(rand() % 256, rand() % 256, rand() % 256, (rand() % 256) / 3);
		particles[particleIndex].size = (rand() % 1000) / 2000.0f + 0.1f;

	}

	int particlesCount = 0;
	for (int i = 0; i<maxParticles; i++)
	{

		Particle& p = particles[i]; // shortcut

		if (p.ttl > 0.0f) {

			// Decrease life
			p.ttl -= delta;
			if (p.ttl > 0.0f) {

				// Simulate simple physics : gravity only, no collisions
				//p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)delta * 0.5f;
				p.pos += p.speed * (float)delta;
				p.cameraDistance = glm::length(p.pos - InputHandler::cameraPos);
				//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

				// Fill the GPU buffer
				particles_position_size_data[4 * particlesCount + 0] = p.pos.x;
				particles_position_size_data[4 * particlesCount + 1] = p.pos.y;
				particles_position_size_data[4 * particlesCount + 2] = p.pos.z;
												 
				particles_position_size_data[4 * particlesCount + 3] = p.size;

				particles_color_data[4 * particlesCount + 0] = p.color.x;
				particles_color_data[4 * particlesCount + 1] = p.color.y;
				particles_color_data[4 * particlesCount + 2] = p.color.z;
				particles_color_data[4 * particlesCount + 3] = p.color.w;

			}
			else {
				// Particles that just died will be put at the end of the buffer in SortParticles();
				p.cameraDistance = -1.0f;
			}

			particlesCount++;

		}
	}

	sortParticles();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * sizeof(GLfloat) * 4, particles_position_size_data);

	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, particlesCount * sizeof(GLubyte) * 4, particles_color_data);

	shader->use();

	/***************************************************/
	glm::vec3 cameraPos = InputHandler::cameraPos;
	glm::vec3 cameraFront = InputHandler::cameraFront;
	glm::vec3 cameraUp = InputHandler::cameraUp;

	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glm::mat4 projection = glm::perspective(45.0f, 1280.0f / 720.0f, 0.001f, 5000.0f);

	glm::mat4 VP = projection * view;
	/***************************************************/


	glBindTexture(GL_TEXTURE_2D, texture);

	//glUniform1i(glGetUniformLocation(shader->id, "myTextureSampler"), 0);

	glUniform3f(glGetUniformLocation(shader->id, "CameraRight_worldspace"), view[0][0], view[1][0], view[2][0]);
	glUniform3f(glGetUniformLocation(shader->id, "CameraUp_worldspace"), view[0][1], view[1][1], view[2][1]);

	glUniformMatrix4fv(glGetUniformLocation(shader->id, "VP"), 1, GL_FALSE, &VP[0][0]);




	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		4,                                // size : x + y + z + size => 4
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		4,                                // size : r + g + b + a => 4
		GL_UNSIGNED_BYTE,                 // type
		GL_TRUE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1
	glVertexAttribDivisor(2, 1); // color : one per quad                                  -> 1

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particlesCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void ParticlesEmitter::initialize()
{
	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	// The VBO containing the colors of the particles
	glGenBuffers(1, &particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
}

void ParticlesEmitter::loadTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE, texture);

	int width, height, nrComponents;
	unsigned char *data = stbi_load("Textures/smoke.png", &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at particle emitter"<< std::endl;
		stbi_image_free(data);
	}

}

int ParticlesEmitter::findUnusedParticle()
{
	for (int i = lastUsedParticle; i<maxParticles; i++) {
		if (particles[i].ttl < 0)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	lastUsedParticle = 0;
	return 0;
}

void ParticlesEmitter::sortParticles()
{
	std::sort(&particles[0], &particles[maxParticles]);
}

