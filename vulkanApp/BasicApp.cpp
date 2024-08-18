#include "BasicApp.hpp"
#include <GLFW/glfw3.h>

namespace Basic {

void BasicApp::run() {
  while (!basicWindow.shouldClose()) {
    glfwPollEvents();
  }
}

} // namespace Basic
