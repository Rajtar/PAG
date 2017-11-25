#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:

	GLuint id;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

private:

	void checkCompileErrors(unsigned int shader, std::string type);
};

