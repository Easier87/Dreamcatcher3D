#pragma once

#include <models/base_includer.hpp>

namespace Dreamcatcher
{

class Cube{
public:
  Cube();
  void draw();
private:
  unsigned int VAO, VBO, EBO;
  std::array<float, 192> cubeVertices;
};


}
