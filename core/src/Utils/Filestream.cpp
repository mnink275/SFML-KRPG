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
        fmt::format("Error during file opening: '{}'", path));
  }

  std::ostringstream buffer;
  buffer << if_stream.rdbuf();
  return buffer.str();
}

}  // namespace ink::utils
