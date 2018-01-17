#include "Mesh.h"
#include "Texture.h"
#include "Cube.h"
#include <iostream>
#include "InputHandler.h"


void Mesh::setupMesh()
{

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);

	/*******************/
	/*glGenVertexArrays(1, &pickingVAO);

	glBindVertexArray(pickingVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);*/
	/*******************/
}

void Mesh::draw(Shader shader)
{
	//glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.use();

	if(this->specialTexture == NULL)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
											  // retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.setFloat(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);
		//std::cout << "drawing!\n";
		// draw mesh
	}
	else //ULTRA WORKAROUND
	{
		/***************************************************/

		glm::mat4 world = glm::mat4(1.0f);

		glm::vec3 cameraPos = InputHandler::cameraPos;
		glm::vec3 cameraFront = InputHandler::cameraFront;
		glm::vec3 cameraUp = InputHandler::cameraUp;

		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glm::mat4 projection = glm::perspective(45.0f, 1280.0f / 720.0f, 0.001f, 5000.0f);

		glm::mat4 WVP = projection * view * world;

		//GLuint wvpLoc = glGetUniformLocation(program->programHandle, "wvp");
		GLuint wvpLoc = glGetUniformLocation(shader.id, "wvp");
		glUniformMatrix4fv(wvpLoc, 1, GL_FALSE, &WVP[0][0]);

		GLuint modelLoc = glGetUniformLocation(shader.id, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &world[0][0]);
		/***************************************************/
		shader.setVec3("cameraPos", InputHandler::cameraPos);
		glBindTexture(GL_TEXTURE_CUBE_MAP, specialTexture);

	}


	glBindVertexArray(VAO);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::drawForPicking(Shader shader)
{
	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}
