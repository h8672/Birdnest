#ifndef modelh
#define modelh

#include "includes.h"
#include "mesh.h"

class Model
{
public:
	// Functions
	Model(GLchar* path);

	void Draw(Shader* shader);
private:
	// Model Data
	std::vector<Mesh> meshes;
	std::string directory;
	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Texture> textures_loaded;
	// Functions
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
};

#endif // !modelh