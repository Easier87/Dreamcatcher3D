#include <models/triangle.hpp>

using namespace Dreamcatcher;

Triangle::Triangle() : vertices{     // vertex positions    // colors
                                      0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
                                     -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
                                      0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
} 

{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glBindVertexArray(0);
}

void Triangle::draw(){
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

