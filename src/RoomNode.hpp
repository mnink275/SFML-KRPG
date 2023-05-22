#pragma once

#include <array>
#include <iostream>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"

class RoomNode final : public SceneNode {
 public:
  RoomNode();

  void buildRoom(sf::Texture& texture, sf::FloatRect bounds);
  void setPlayer(Ptr player);
  Ptr getPlayer();

 private:
  enum Layer { Background, Air, LayerCount };

  std::array<SceneNode*, LayerCount> mRoomLayers;
};
