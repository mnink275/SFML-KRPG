#include <Utils/Filestream.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <fmt/format.h>

namespace ink::utils {

std::string readFileContent(const std::string& path) {
  std::ifstream if_stream(path);
  if (!if_stream.is_open()) {
    throw std::runtime_error(
        fmt::format("Error opening the file for reading: '{}'", path));
  }

  std::ostringstream buffer;
  buffer << if_stream.rdbuf();
  return buffer.str();
}

void writeFileContent(const std::string& path, const std::string& content) {
  std::ofstream of_stream(path, std::ios::trunc);
  if (!of_stream.is_open()) {
    throw std::runtime_error(
        fmt::format("Error opening the file for writing: '{}'", path));
  }
  of_stream << content;
}

}  // namespace ink::utils
