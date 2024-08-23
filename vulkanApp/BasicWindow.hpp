#pragma once

#include <cstdint>
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
  VkExtent2D getExtent() {
    return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
  }
  void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
  GLFWwindow *window;
  const int width;
  const int height;
  std::string windowName;
  void initWindow();
};

} // namespace Basic
