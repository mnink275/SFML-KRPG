#pragma once

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

namespace ink {

class Player final : public Entity {
 public:
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;

  Player(Player&&) = delete;
  Player& operator=(Player&&) = delete;

  ~Player() = default;

  enum Type {
    Peepo,
  };

  Player(Type type, const TextureHolder& textures);
  void drawCurrent(sf::RenderTarget& target,
                   sf::RenderStates states) const override;

 private:
  Type type_;
  sf::Sprite sprite_;
};

}  // namespace ink
