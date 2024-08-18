#include "BasicPipeline.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
namespace Basic {

std::vector<char> BasicPipeline::readFile(const std::string &fileName) {

  std::ifstream file(fileName, std::ios::ate | std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open files: " + fileName);
  }
  size_t fileSize = static_cast<size_t>(file.tellg());
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);
  file.close();
  return buffer;
}
void BasicPipeline::createBasicPipeline(const std::string &vertFilePath,
                                        const std::string &fragFilePath) {
  auto vertCode = readFile(vertFilePath);
  auto fragCode = readFile(fragFilePath);
  std::cout << "V. Shader Code Size: " << vertCode.size() << std::endl;
  std::cout << "F. Shader Code Size: " << fragCode.size() << std::endl;
}
BasicPipeline::BasicPipeline(const std::string &vertFilePath,
                             const std::string &fragFilePath) {
  createBasicPipeline(vertFilePath, fragFilePath);
}
} // namespace Basic
