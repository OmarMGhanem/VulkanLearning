#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
namespace Basic {

class BasicWindow {

public:
  BasicWindow(int w, int h, std::string name);
  ~BasicWindow();
  BasicWindow(const BasicWindow &) = delete;
  BasicWindow &operator=(const BasicWindow &) = delete;
  bool shouldClose() { return glfwWindowShouldClose(window); }

private:
  GLFWwindow *window;
  const int width;
  const int height;
  std::string windowName;
  void initWindow();
};

} // namespace Basic
