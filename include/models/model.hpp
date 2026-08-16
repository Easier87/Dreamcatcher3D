#pragma once

#include <models/mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb-master/stb_image.h>

namespace Dreamcatcher
{

class Model
{
public:
  Model (char *path)
  {
    loadModel(path);
  }
  void Draw(Shader &shader);

private:
  std::vector<Texture> textures_loaded;
  std::vector<Mesh> meshes;
  std::string directory;

  void loadModel(std::string path);
  std::vector<Texture> loadMaterialTextures(aiMaterial *material, aiTextureType type, std::string typeName);
  unsigned int TextureFromFile(const char *path, const std::string &directory);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};

}
