#pragma once

#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include <Wall.hpp>

namespace ink {

class Editor final {
 private:
  using WallIter = std::list<Wall>::iterator;

 public:
  Editor();

  Editor(const Editor&) = delete;
  Editor& operator=(const Editor&) = delete;

  Editor(Editor&&) = delete;
  Editor& operator=(Editor&&) = delete;

  ~Editor() = default;

  void run();

 private:
  void processEvents();
  void update(sf::Time dt);
  void render();

  void handleMouseInput(const sf::Event::MouseButtonEvent event,
                        bool is_pressed);
  void handleKeyPressed(const sf::Keyboard::Key key);

  void createNewWall();
  WallIter tryFindActiveWall(const sf::Vector2f mouse_pos);

  void serialize() const;

 private:
  const sf::Time kTimePerFrame;
  sf::RenderWindow window_;

  std::list<Wall> walls_;
  WallIter active_wall_it_;

  sf::Vector2f last_mouse_pos_;
};

}  // namespace ink
