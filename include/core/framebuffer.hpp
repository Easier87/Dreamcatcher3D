#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/window.hpp>
#include <array>

namespace Dreamcatcher{

class Framebuffer{
public:
  Framebuffer(const Window& window);
  // void DrawFramebuffer();
  GLuint GetBuffer() { return FBO; };
  GLuint GetTexture() { return texture; };
  // void GetBramebufferSize();
private:
  GLuint FBO, texture, RBO;
  // GLuint quadVAO, quadVBO, EBO;
  std::array<float, 16> quad;
};

}
