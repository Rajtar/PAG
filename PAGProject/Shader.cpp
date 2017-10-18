#include "Shader.h"
#include <fstream>
#include <iostream>

void Shader::loadShader(std::string filename)
{
	std::string line;
	std::ifstream file(filename);

	if (!file)
	{
		std::cerr<<"Could not open file "<<filename<<std::endl;
		file.close();
	}
	else
	{
		while (file.good())
		{
			getline(file, line);
			shaderData.append(line + "\n");
		}

		file.close();
	}
}

void Shader::loadAndCompileShaderFromFile(GLint shaderType, std::string filename, GLuint & programHandle)
{
	GLuint shaderObject = glCreateShader(shaderType);

	if (shaderObject == 0)
	{
		std::cerr<<"Error creating "<<filename<<std::endl;
		return;
	}

	loadShader(filename);

	if (shaderData.empty())
	{
		std::cerr << "Shader file " << filename << " is empty!" << std::endl;
	}

	const char * shaderDataChars = shaderData.c_str();
	const GLint dataSize = shaderData.size();

	glShaderSource(shaderObject, 1, &shaderDataChars, &dataSize);
	glCompileShader(shaderObject);

	GLint compilationStatus;
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &compilationStatus);

	if (compilationStatus == GL_FALSE)
	{
		std::cerr << "Compilation of shader: " << filename << " failed!" << std::endl;

		GLint logLength;
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)
		{
			char* log = new char(logLength);

			GLsizei logRead;
			glGetShaderInfoLog(shaderObject, logLength, &logRead, log);

			std::cerr << "Log:\n" << log << std::endl;

			delete log;
		}
	}

	glAttachShader(programHandle, shaderObject);
	glDeleteShader(shaderObject);
}


std::string Shader::getShaderData()
{
	return shaderData;
}

Shader::Shader()
{
}


Shader::~Shader()
{
}
