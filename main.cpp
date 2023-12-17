#include <Game.hpp>

#include <fmt/core.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Utils/Filestream.hpp>
int main() {
  try {
    // auto str = ink::utils::readFileContent("./data/first_room_walls.txt");
    // auto view = str;
    // std::size_t left = 0;
    // std::size_t right = 0;
    // std::size_t idx = 0;
    // while (left < str.size()) {
    //   right = view.find_first_of(" \n", left);
    //   fmt::println("{}", view.substr(left, right - left));
    //   left = right + 1;
    // }
    
    ink::Game game;
    game.run();
  } catch (std::exception& e) {
    fmt::println("Exception: {}", e.what());
  }
}