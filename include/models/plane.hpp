#pragma once

#include <models/base_includer.hpp>

namespace Dreamcatcher{

class Plane{
public:
  Plane();
  void draw();
private:
  unsigned int VAO, VBO, EBO;
  std::array<float, 32> rectangleVertices; 
};

}
