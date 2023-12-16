#include <Game.hpp>

#include <fmt/core.h>
#include <iostream>

#include <SFML/Graphics.hpp>

int main() {
  try {
    ink::Game game;
    game.run();
  } catch (std::exception& e) {
    fmt::println("Exception: {}", e.what());
  }
}