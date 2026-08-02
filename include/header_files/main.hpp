#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <models/triangle.hpp>
#include <models/rectangle.hpp>
#include <core/shader.hpp>
#include <stb-master/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

namespace Dreamcatcher{
  inline void framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
  }

}
