#pragma once

#include <array>
#include <iostream>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"

class RoomNode final : public SceneNode {
 public:
  RoomNode() = default;

  void buildRoom(sf::Texture& texture, sf::FloatRect bounds);
  void setPlayer(Ptr player);
  Ptr popPlayer() const;

 private:
  enum Layer { Background, Air, LayerCount };

  std::array<SceneNode*, LayerCount> room_layers_{nullptr};
};
