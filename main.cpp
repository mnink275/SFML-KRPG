#include <Game.hpp>

#include <fmt/core.h>

int main() {
  try {
    ink::Game game;
    game.run();
  } catch (const std::exception& e) {
    fmt::println("Exception: {}", e.what());
  }
}
