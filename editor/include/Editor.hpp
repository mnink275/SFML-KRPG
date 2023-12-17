#pragma once

#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include <Wall.hpp>

namespace ink {

class Game final {
 public:
  Game();

  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;

  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

  ~Game() = default;

  void run();

 private:
  void processEvents();
  void update(sf::Time dt);
  void render();

  void handleMouseInput(const sf::Event::MouseButtonEvent event,
                        bool is_pressed);
  void handleKeyPressed(const sf::Keyboard::Key key);

 private:
  const sf::Time kTimePerFrame;
  sf::RenderWindow window_;

  std::list<Wall> walls_;
  using Iterator = std::list<Wall>::iterator;
  Iterator active_wall_it_;
};

}  // namespace ink
