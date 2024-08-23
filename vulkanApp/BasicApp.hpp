#pragma once
#include "BasicDevice.hpp"
#include "BasicPipeline.hpp"
#include "BasicWindow.hpp"

namespace Basic {

class BasicApp {

public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;
  void run();

private:
  BasicWindow basicWindow{WIDTH, HEIGHT, "BasicWindow_BasicApp"};
  BasicDevice basicDevice{basicWindow};
  BasicPipeline basicPipeline{
      basicDevice, "build/shaders/BasicShader.vert.spv",
      "build/shaders/BasicFragmentShader.frag.spv",
      BasicPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
};

} // namespace Basic
