#include <SFML/Graphics.hpp>
#include <iostream>
#include "Core.hpp"

int main() {
  try {
    Game game;
    game.run();
  } catch (std::exception& e) {
    std::cout << "\nEXCEPTION: " << e.what() << std::endl;
  }
}