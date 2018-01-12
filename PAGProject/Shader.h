#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/detail/type_vec3.hpp>

class Shader
{
public:

	GLuint id;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;

private:

	void checkCompileErrors(unsigned int shader, std::string type);
};

