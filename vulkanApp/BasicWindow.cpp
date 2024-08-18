#include "BasicWindow.hpp"
#include <GLFW/glfw3.h>

namespace Basic {

BasicWindow::BasicWindow(int w, int h, std::string name)
    : width{w}, height(h), windowName(name) {
  initWindow();
}

BasicWindow::~BasicWindow() {
  glfwDestroyWindow(window);
  glfwTerminate();
}
void BasicWindow::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window =
      glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

} // namespace Basic
