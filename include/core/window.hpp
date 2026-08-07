#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

const int WIN_WIDTH  = 800;
const int WIN_HEIGHT = 600;

namespace Dreamcatcher
{

class Window
{
public:
  Window(int width = WIN_WIDTH, int height = WIN_HEIGHT, const std::string title = "Dreamcatcher3D");
  ~Window();
  
  // prohibition of copying
  Window(const Window&) = delete;
  Window& operator = (const Window&) = delete;

  GLFWwindow* GetHandle() const { return window;   };
  int         GetWidth()  const { return m_width;  };
  int         GetHeight() const { return m_height; };

  bool ShouldClose() const;
  void SwapBuffers() const;
  void PollEvents() const;

private:
  GLFWwindow* window = nullptr;
  int m_width, m_height;
  bool WindowInit(std::string title);
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
  // static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
  // static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

}
