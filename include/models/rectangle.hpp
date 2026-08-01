#pragma once

#include <models/base_includer.hpp>

namespace Dreamcatcher{

class Rectangle{
public:
  Rectangle();
  void draw();
private:
  unsigned int VAO, VBO;
  std::array<float, 36> rectangleVertices; 
};

}
