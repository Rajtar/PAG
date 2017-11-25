#include "Texture.h"
#include "ImageLoader.cpp"
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


//void Texture::loadTexture(std::string filename)
//{
//	unsigned int texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	int width, height, nrChannels;
//	unsigned char *fileData = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
//	if (fileData)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, fileData);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cerr << "Failed to load texture" << std::endl;
//	}
//	stbi_image_free(fileData);
//
//	id = texture;
//}
//
//unsigned int Texture::getTextureHolder()
//{
//	return id;
//}
//
//Texture::Texture()
//{
//}


//Texture::~Texture()
//{
//}
