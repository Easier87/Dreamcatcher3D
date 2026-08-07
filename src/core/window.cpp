#include <core/window.hpp>

using namespace Dreamcatcher;

Window::Window(int width, int height, const std::string title) : m_width(width), m_height(height) {
  if(!WindowInit(title)){
    std::cout << "Failed to create window!" << std::endl;
  }
}

Window::~Window(){
  if (m_window)
    glfwDestroyWindow(m_window);
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
  if (!glfwInit()){
    std::cout << "glfwInit failed!" << std::endl;
    return false;

  }

  m_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Dreamcatcher3D", NULL, NULL);
  if (!m_window)
  {
    std::cout << "Failed to load GLFW window!" << std::endl;
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(m_window);
  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  // glfwSetCursorPosCallback(m_window, mouse_callback);
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
  return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers() const{
  return glfwSwapBuffers(m_window);
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
