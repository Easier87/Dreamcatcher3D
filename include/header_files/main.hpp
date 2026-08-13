#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <skybox.hpp>

#include <models/triangle.hpp>
#include <models/plane.hpp>
#include <models/cube.hpp>

#include <core/shader.hpp>
#include <core/camera.hpp>
#include <core/window.hpp>
#include <core/framebuffer.hpp>

#include <stb-master/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// namespace Dreamcatcher{
//   inline void framebuffer_size_callback(GLFWwindow *window, int width, int height){
//     glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
//   }
//
// }
