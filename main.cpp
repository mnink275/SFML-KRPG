#include <Game.hpp>

#include <fmt/core.h>

#include <SFML/Graphics.hpp>

int main() {
  try {
    ink::Game game;
    game.run();
  } catch (std::exception& e) {
    fmt::print("Exception: ", e.what());
  }
}