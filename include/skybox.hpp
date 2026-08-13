#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include <string>
#include <vector>
#include <stb-master/stb_image.h>
#include <iostream>

namespace Dreamcatcher
{

class Skybox
{
public:
  Skybox();
  void draw();
private:
  unsigned int VAO, VBO, cubemapTexture;
  GLuint loadCubemap(std::vector<std::string> faces);
  std::array<GLfloat, 108> skyboxVertices;
};

}
