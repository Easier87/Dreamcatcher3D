#pragma once

#include <models/base_includer.hpp>

namespace Dreamcatcher{

class Rectangle{
public:
  Rectangle();
  void draw();
private:
  unsigned int VAO, VBO, EBO;
  std::array<float, 32> rectangleVertices; 
};

}
