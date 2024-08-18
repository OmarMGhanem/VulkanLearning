#pragma once

#include "BasicWindow.hpp"

namespace Basic {

class BasicApp {

public:
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;
  void run();

private:
  BasicWindow basicWindow{WIDTH, HEIGHT, "BasicWindow_BasicApp"};
};

} // namespace Basic
