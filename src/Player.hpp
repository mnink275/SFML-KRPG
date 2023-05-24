#pragma once

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class Player final : public Entity {
 public:
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