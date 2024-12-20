#ifndef MODEL_H
#define MODEL_H

#include<glad/glad.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<stb_image.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include<Mesh.h>
#include<Shader.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<map>
#include<vector>

class Model {
public:
	Model(char	*path);
	void Draw(Shader &shader);

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif // !MODEL_H
