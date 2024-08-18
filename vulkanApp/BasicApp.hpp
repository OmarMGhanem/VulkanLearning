#pragma once
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
  BasicPipeline basicPipeline{"build/shaders/BasicShader.vert.spv",
                              "build/shaders/BasicFragmentShader.frag.spv"};
};

} // namespace Basic
