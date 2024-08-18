#pragma once

#include <string>
#include <vector>

namespace Basic {

class BasicPipeline {
public:
  BasicPipeline(const std::string &vertFilePath,
                const std::string &fragFilePath);

private:
  static std::vector<char> readFile(const std::string &fileName);
  void createBasicPipeline(const std::string &vertFilePath,
                           const std::string &fragFilePath);
};

} // namespace Basic
