#include <fmt/core.h>

#include <Editor.hpp>

int main() {
  try {
    ink::Game editor;
    editor.run();
  } catch (const std::exception& e) {
    fmt::println("Exception: {}", e.what());
  }
}
