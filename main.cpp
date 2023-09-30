#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

int main() {
  try {
    ink::Game game;
    game.run();
  } catch (std::exception& e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }
}