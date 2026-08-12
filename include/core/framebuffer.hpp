#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/window.hpp>

#include <iostream>

namespace Dreamcatcher{

class Framebuffer{
public:
  Framebuffer();
  GLuint GetBuffer() { return FBO; };
  GLuint GetTexture() { return texture; };
private:
  GLuint FBO, texture, RBO;
};

}
