#pragma once

#include <string>

class Texture
{
public:

	void loadTexture(std::string filename);
	unsigned int getTextureHolder();

	Texture();
	~Texture();

private:

	unsigned int textureHolder;

};

