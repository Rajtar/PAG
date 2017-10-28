#include "Program.h"
#include <iostream>


void Program::linkProgram()
{
	glLinkProgram(programHandle);

	GLint linkingStatus;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &linkingStatus);

	if (linkingStatus == GL_FALSE)
	{
		std::cerr << "Failed to link shader program!\n";

		GLint logLength;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)
		{
			char* log = new char(logLength);

			GLsizei logRead;
			glGetProgramInfoLog(programHandle, logLength, &logRead, log);

			std::cerr << "Log:\n" << log << std::endl;

			delete log;
		}
	}
}

void Program::activateProgram()
{
	glUseProgram(programHandle);
}

Program::Program()
{
	programHandle = glCreateProgram();

	if (programHandle == 0)
	{
		std::cerr << "Error creating program object.\n";
	}
}


Program::~Program()
{
}
