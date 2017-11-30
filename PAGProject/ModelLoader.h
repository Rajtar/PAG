#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "GraphNode.h"

class ModelLoader
{
public:

	void loadModel(std::string path, GraphNode* modelRootNode, Shader* shader);

private:
	std::string directory;

	std::vector<unsigned int> uniqueIdentifiers;

	unsigned int assignUniqueId();

	void processNode(aiNode* node, const aiScene* scene, GraphNode* parentNode, Shader* shader);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned TextureFromFile(const char* path, const std::string& directory, bool gamma);
};

