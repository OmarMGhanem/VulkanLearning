#pragma once
#include "BasicDevice.hpp"
#include "BasicPipeline.hpp"
#include "BasicSwapChain.hpp"
#include "BasicWindow.hpp"

#include <memory>
#include <vector>
#include <vulkan/vulkan_core.h>
namespace Basic {

class BasicApp {

public:
  BasicApp();
  ~BasicApp();

  BasicApp(const BasicApp &) = delete;
  BasicApp &operator=(const BasicApp &) = delete;

  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;
  void run();

private:
  void createPipelineLayout();
  void createPipeline();
  void createCommandBuffers();
  void drawFrame();
  BasicWindow basicWindow{WIDTH, HEIGHT, "BasicWindow_BasicApp"};
  BasicDevice basicDevice{basicWindow};
  BasicSwapChain basicSwapChain{basicDevice, basicWindow.getExtent()};
  std::unique_ptr<BasicPipeline> basicPipeline;
  VkPipelineLayout pipelineLayout;
  std::vector<VkCommandBuffer> commandBuffers;
};
} // namespace Basic
