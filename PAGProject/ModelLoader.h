#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "ModelNode.h"
#include <map>

class ModelLoader
{
public:

	void loadModel(std::string path, ModelNode* modelRootNode, Shader* drawingShader, Shader* pickingShader);
	void loadModelOmmitingRoot(std::string path, ModelNode *modelRootNode, Shader* drawingShader, Shader* pickingShader);

	std::map<int, ModelNode*> loadedNodes;

private:

	std::string directory;

	unsigned short idCounter = 0;

	void processNode(aiNode* node, const aiScene* scene, ModelNode* parentNode, Shader* drawingShader, Shader* pickingShader);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned TextureFromFile(const char* path, const std::string& directory, bool gamma);
};

