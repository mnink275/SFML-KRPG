#pragma once

#include <string>

namespace ink::utils {

std::string readFileContent(const std::string& path);

void writeFileContent(const std::string& path, const std::string& content);

}  // namespace ink::utils
