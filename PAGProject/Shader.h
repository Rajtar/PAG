#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:

	void loadShader(std::string filename);
	void loadAndCompileShaderFromFile(GLint shaderType, std::string filename, GLuint& programHandle);

	std::string getShaderData();

	Shader();
	~Shader();

private:

	std::string shaderData;
};

