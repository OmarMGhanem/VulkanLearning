#include "BasicApp.hpp"
#include "BasicPipeline.hpp"
#include <GLFW/glfw3.h>
#include <array>
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vulkan/vulkan_core.h>
namespace Basic {

BasicApp::BasicApp() {
  createPipelineLayout();
  createPipeline();
  createCommandBuffers();
}

BasicApp::~BasicApp() {
  vkDestroyPipelineLayout(basicDevice.device(), pipelineLayout, nullptr);
}

void BasicApp::run() {
  while (!basicWindow.shouldClose()) {
    glfwPollEvents();
    drawFrame();
  }
  vkDeviceWaitIdle(basicDevice.device());
}
void BasicApp::createPipelineLayout() {
  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0;
  pipelineLayoutInfo.pSetLayouts = nullptr;
  pipelineLayoutInfo.pushConstantRangeCount = 0;
  pipelineLayoutInfo.pPushConstantRanges = nullptr;

  if (vkCreatePipelineLayout(basicDevice.device(), &pipelineLayoutInfo, nullptr,
                             &pipelineLayout) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create pipeline layout!");
  }
}

void BasicApp::createPipeline() {
  auto pipelineConfig = BasicPipeline::defaultPipelineConfigInfo(
      basicSwapChain.width(), basicSwapChain.height());
  pipelineConfig.renderPass = basicSwapChain.getRenderPass();
  pipelineConfig.pipelineLayout = pipelineLayout;

  basicPipeline = std::make_unique<BasicPipeline>(
      basicDevice, "build/shaders/BasicShader.vert.spv",
      "build/shaders/BasicFragmentShader.frag.spv", pipelineConfig);
}

void BasicApp::createCommandBuffers() {
  commandBuffers.resize(basicSwapChain.imageCount());
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = basicDevice.getCommandPool();
  allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

  if (vkAllocateCommandBuffers(basicDevice.device(), &allocInfo,
                               commandBuffers.data()) != VK_SUCCESS) {
    throw std::runtime_error("Failed to create command buffruntime_errorers");
  }
  for (int i = 0; i < commandBuffers.size(); i++) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
      throw std::runtime_error("Command buffer failed recording");
    }
    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = basicSwapChain.getRenderPass();
    renderPassInfo.framebuffer = basicSwapChain.getFrameBuffer(i);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = basicSwapChain.getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();
    vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo,
                         VK_SUBPASS_CONTENTS_INLINE);
    basicPipeline->bind(commandBuffers[i]);
    vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
    vkCmdEndRenderPass(commandBuffers[i]);

    if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
      throw std::runtime_error("Failed to record command buffer!");
    }
  }
}
void BasicApp::drawFrame() {
  uint32_t imageIndex;
  auto result = basicSwapChain.acquireNextImage(&imageIndex);

  if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw std::runtime_error("failed to acquire swap chain image!");
  }

  result = basicSwapChain.submitCommandBuffers(&commandBuffers[imageIndex],
                                               &imageIndex);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Failed to present swap chain image!");
  }
}

} // namespace Basic
