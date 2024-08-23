#pragma once

#include "BasicDevice.hpp"
#include <cstdint>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace Basic {

struct PipelineConfigInfo {
  VkViewport viewport;
  VkRect2D scissor;
  VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
  VkPipelineRasterizationStateCreateInfo rasterizationInfo;
  VkPipelineMultisampleStateCreateInfo multisampleInfo;
  VkPipelineColorBlendAttachmentState colorBlendAttachment;
  VkPipelineColorBlendStateCreateInfo colorBlendInfo;
  VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
  VkPipelineLayout pipelineLayout = nullptr;
  VkRenderPass renderPass = nullptr;
  uint32_t subpass = 0;
};

class BasicPipeline {
public:
  BasicPipeline(BasicDevice &device, const std::string &vertFilePath,
                const std::string &fragFilePath,
                const PipelineConfigInfo &configInfo);
  ~BasicPipeline();
  BasicPipeline(const BasicPipeline &) = delete;
  void operator=(const BasicPipeline) = delete;
  void bind(VkCommandBuffer commandBuffer);

  static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width,
                                                      uint32_t height);

private:
  static std::vector<char> readFile(const std::string &fileName);
  void createBasicPipeline(const std::string &vertFilePath,
                           const std::string &fragFilePath,
                           const PipelineConfigInfo &configInfo);
  void createShaderModule(const std::vector<char> &code,
                          VkShaderModule *shaderModule);
  BasicDevice &basicDevice; // shouldn't be safe, but the device instance should
                            // outlive any pipeline.
  VkPipeline graphicsPipeline;
  VkShaderModule vertShaderModule;
  VkShaderModule fragShaderModule;
};

} // namespace Basic
