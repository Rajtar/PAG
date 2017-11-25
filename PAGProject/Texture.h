#pragma once

#include <string>
#include <assimp/types.h>

class Texture
{
public:

	unsigned int id;
	aiString path;
	std::string type;

	/*void loadTexture(std::string filename);
	unsigned int getTextureHolder();

	Texture();
	~Texture();*/
};

