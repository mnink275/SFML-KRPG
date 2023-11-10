#pragma once

#include <SFML/Graphics.hpp>

#include <Resource/ResourceIdentifiers.hpp>
#include <World.hpp>

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
  void update(sf::Time elapsed_time);
  void render();

  void updateStatistics(sf::Time elapsed_time);

  TextureHolder loadTextures();
  FontHolder loadFonts();

 private:
  const sf::Time kTimePerFrame;

  const std::string kResourcePath;
  TextureHolder textures_;
  FontHolder fonts_;

  sf::RenderWindow window_;
  World world_;

  sf::Text statistics_text_;
  sf::Time statistics_update_time_;
  std::size_t statistics_num_frames_;
};

}  // namespace ink
