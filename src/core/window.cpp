#include <core/window.hpp>

using namespace Dreamcatcher;

Window::Window(int width, int height, const std::string title) : m_width(width), m_height(height) {
  if(!WindowInit(title)){
    std::cout << "Failed to create window!" << std::endl;
  }
}

Window::~Window(){
  if (!window)
    glfwDestroyWindow(window);
  glfwTerminate();
}

bool Window::WindowInit(std::string title){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  GLFWwindow* window;

  if (!glfwInit())
    return false;

  window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Dreamcatcher3D", NULL, NULL);
  if (!window)
  {
    std::cout << "Failed to load GLFW window!" << std::endl;
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // glfwSetCursorPosCallback(window, mouse_callback);
  // glfwSetScrollCallback(window, scroll_callback);
  
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD!" << std::endl;
    return false;
  }

  return true;
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height){
  Window* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if (self){
    self->m_width = width;
    self->m_height = height;
  }
  glViewport(0, 0, width, height);
}

bool Window::ShouldClose() const{
  return glfwWindowShouldClose(window);
}

void Window::SwapBuffers() const{
  return glfwSwapBuffers(window);
}

void Window::PollEvents() const{
  return glfwPollEvents();
}

// void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos){
//   float xoffset = xpos - lastX;
//   float yoffset = lastY - ypos;
//
//   lastX = xpos;
//   lastY = ypos;
//
//
// }
//
// void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
//
// }
